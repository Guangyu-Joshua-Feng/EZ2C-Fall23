#include "ez2c_master.h"

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>
#include <pico/unique_id.h>

#include "circular_buffer.h"
#include "ez2c_common.h"
#include "rise_time_noblock.h"
#include "uint32_array.h"

// ---------------------------- Defined Constants ------------------------------

// The stall handler function will attempt to read this number of bytes
// in attempts to reconnect to the slave.
#define STALL_RECOVERY_NUM_TEST_BYTES 2

// Maximum number of pull-up resistance levels supported. Since we use a
// static array to store the addresses, we need to predefine a length for
// it. This value can be increased in the future. The only limitation to
// this value is the amount of static memory of the target device.
#define NUM_PULL_UP_LEVELS_MAX 8

// -------------------------------- Constants ----------------------------------

// Default I2C R/W timeout in milliseconds. All non-user initiated I2C
// communications will use this value as timeout for stall detection.
static const uint I2C_DEFAULT_TIMEOUT_MS = 1000u;

// The PIO cycle counter will assert an interrupt and report the average rise
// time every this number of rises under normal operation.
static const uint PIO_NORMAL_RISE_COUNT_LIMIT = UINT32_ARRAY_SIZE;

// The PIO cycle counter will assert an interrupt and report the average rise
// time every this number of rises when attempting a stall recovery.
static const uint PIO_RECOVERY_RISE_COUNT_LIMIT = 8u;

static const float SLAVE_INTERRUPT_RISE_TIME_DIFF_THRESHOLD = 180.0f;

// An absolute rise time difference no greater than this value is considered
// noise under stable connection.
static const float RISE_TIME_CYCLES_STABLE_THRESHOLD = 5.0f;

// Used together with ref_safe_rise_cycles. The system will attempt to increase
// pull-up resistance when a new average rise time is smaller than this factor
// times ref_safe_rise_cycles to conserve energy.
static const float SAFE_RISE_TIME_LOWER_BOUND_FACTOR = 0.8f;

// Used together with ref_safe_rise_cycles. The system will attempt to decrease
// pull-up resistance when a new average rise time is greater than this factor
// times ref_safe_rise_cycles to ensure stable connection.
static const float SAFE_RISE_TIME_UPPER_BOUND_FACTOR = 1.01f;

// ---------------------------- Global Variables -------------------------------

// I2C hardware in use as master.
static i2c_inst_t *i2c_hw;

// PIO hardware in use for I2C SCL (clock) rise time cycle counter.
static PIO scl_pio_hw;

// PIO hardware in use for I2C SDA (data) rise time cycle counter.
static PIO sda_pio_hw;

// PIO state machine number for I2C SCL (clock) rise time cycle counter.
static uint scl_sm;

// PIO state machine number for I2C SDA (data) rise time cycle counter.
static uint sda_sm;

// Pull-up resistance controller demux output pins. Provided by the user and
// only set once by the master initialization function.
static uint pull_up_demux_pins[NUM_PULL_UP_LEVELS_MAX];

// Stores the reserved status of all available relative slave addresses.
// The actual slave address is calculated as (relative_addr + default_addr + 1).
static bool addr_reserved[EZ2C_SLAVES_MAX];

// Flag indicating whether a stall has happened and been recovered from.
// The system will attempt to set ref_safe_rise_cycles immediately after it
// recovers from its first I2C stall.
static bool first_stall_recovered;

// Flag indicating whether ref_safe_rise_cycles has been set. Otherwise,
// it contains garbage value and should not be used.
static bool ref_safe_rise_cycles_set;

// A reference rise time in number of cycles that is safe for I2C communication
// under the current hardware configuration.
static float ref_safe_rise_cycles;

// Number of bits currently used to represent a pull-up resistance level.
// E.g., if set to 2, than there are 4 levels 0-3 available.
static uint8_t pull_up_level_bits;

// Current pull-up resistance level.
static uint curr_pull_up_level;

// Flag indicating that pull-up resistance level was recently adjusted.
// Used in stall recovery mode to determine whether we can still adjust
// pull-up resistance according to PIO rise time measurement results.
static bool pullup_adjusted;

// Buffer containing recently measured rise time in number of cycles by the PIO
// rise time program.
static circular_buffer_t recent_rise_cycles;

static uint curr_rise_count_limit;

static uint32_array_t scl_buffer;
static uint32_array_t sda_buffer;
static uint32_array_t propagated_sda_buffer;

// Flag indicating if there's a pending device change. A pending change will
// become a formal change once the recent rise time measurement becomes stable.
static bool device_change_pending;

static bool slave_interrupt_pending;

// Flag indicating if there's a device change since the last time this flag was
// cleared.
static bool device_change;

// ---------------------------- Helper Functions -------------------------------

// ez2c_master_init

static void init_global_variables();
static void init_pull_up_demux(const uint *_pull_up_demux_pins,
                               uint _pull_up_level_bits);
static void init_pio_rise_time_cycle_counter(uint scl_lo_pin, uint scl_hi_pin,
                                             uint sda_lo_pin, uint sda_hi_pin);
static uint init_i2c(i2c_inst_t *i2c, uint baudrate, uint sda_pin, uint scl_pin,
                     bool internal_pullup);

static inline uint pull_up_levels();
static inline uint pull_up_level_max();

// PIO IRQ Handler and related helper functions

static void pio_scl_counter_irq_handler();
static void scl_irq_handler_helper(int irq);

static void pio_sda_counter_irq_handler();
static void sda_irq_handler_helper(int irq);

static bool adjust_pullup_conditional(float cycles);
static uint adjust_pullup_level(int offset);
static uint set_pullup_level(uint level);

static inline float rise_cycles_control_max();
static inline float rise_cycles_control_min();

static void detect_device_change(float new_avg_cycles, bool pullup_adjusted);
static bool is_new_avg_cycles_stable(float cycles);
static bool is_recent_stable();

// ez2c_master_discover

static bool discover_slave();
static bool assign_slave_addr(pico_unique_board_id_t id);
static uint8_t reserve_next_addr();
static inline uint8_t addr_at_index(int i);

// ez2c_master_clear_slave_interrupt

static bool poll_slave_interrupt(uint8_t addr);

// ez2c_master_write_timeout_ms, ez2c_master_read_timeout_ms

static void stall_handler(uint8_t slave_addr);
static uint8_t step_pullup_level();

// -----------------------------------------------------------------------------

uint ez2c_master_init(i2c_inst_t *i2c, uint baudrate, uint sda_pin,
                      uint scl_pin, uint pio_scl_lo_pin, uint pio_scl_hi_pin,
                      uint pio_sda_lo_pin, uint pio_sda_hi_pin,
                      const uint *_pull_up_demux_pins, uint _pull_up_level_bits,
                      bool internal_pullup) {
    static bool once = false;
    if (!once) {
        once = true;
    } else {
        printf(
            "ez2c_master_init: (WARNING) master already initialized, "
            "aborting...\n");
        return 0;
    }

    init_global_variables();
    init_pull_up_demux(_pull_up_demux_pins, _pull_up_level_bits);
    init_pio_rise_time_cycle_counter(pio_scl_lo_pin, pio_scl_hi_pin,
                                     pio_sda_lo_pin, pio_sda_hi_pin);
    return init_i2c(i2c, baudrate, sda_pin, scl_pin, internal_pullup);
}

/** Dynamic slave address allocation steps:
 *  1. Boardcast discover command to the default slave address.
 *  2. Read response, which should contain the unique identifier of a device
 *     whose address is yet to be assigned, or fail if no device is waiting
 *     to be discovered.
 *  3. If at least one response is read, go to 4; otherwise, go to 7.
 *  4. Get the next unused slave address from table and increment slave
 *     counter.
 *  5. Send address reassignment command + unique identifier + new address
 *     to the slave. Only the slave with the right unique identifier will
 *     change their address accordingly.
 *  6. Go to 1 and restart the procedure until all slaves have their unique
 *     addresss.
 *  7. Done
 */
int ez2c_master_discover() {
    int count = 0;
    bool discovered = true;

    while (discovered) {
        discovered = discover_slave();
        count += discovered;
    }

    return count;
}

bool ez2c_master_slave_addr_exists(uint8_t addr) {
    if (addr <= I2C_DEFAULT_SLAVE_ADDR) return false;
    if (addr > I2C_DEFAULT_SLAVE_ADDR + EZ2C_SLAVES_MAX - 1) return false;
    return addr_reserved[addr - I2C_DEFAULT_SLAVE_ADDR - 1];
}

bool ez2c_get_device_change() { return device_change; }

void ez2c_clear_device_change() { device_change = false; }

int ez2c_master_write_timeout_ms(uint8_t addr, const uint8_t *src, size_t len,
                                 bool nostop, uint timeout_ms) {
    uint timeout_us = timeout_ms * US_PER_MS;
    int ret = i2c_write_timeout_us(i2c_hw, addr, src, len, nostop, timeout_us);

    // A timeout likely indicates that the pullup resistance is incorrectly set.
    while (ret == PICO_ERROR_TIMEOUT) {
        // Initiate recovery subroutine.
        stall_handler(addr);
        // Retry I2C write.
        ret = i2c_write_timeout_us(i2c_hw, addr, src, len, nostop, timeout_us);
    }

    return ret;
}

int ez2c_master_read_timeout_ms(uint8_t addr, uint8_t *dst, size_t len,
                                bool nostop, uint timeout_ms) {
    uint timeout_us = timeout_ms * US_PER_MS;
    int ret = i2c_read_timeout_us(i2c_hw, addr, dst, len, nostop, timeout_us);

    // A timeout likely indicates that the pullup resistance is incorrectly set.
    while (ret == PICO_ERROR_TIMEOUT) {
        // Initiate recovery subroutine.
        stall_handler(addr);
        // Retry I2C read.
        ret = i2c_read_timeout_us(i2c_hw, addr, dst, len, nostop, timeout_us);
    }

    return ret;
}

// TODO: this should eventually go away.
static uint32_t *propagate_sda_buffer(void) {
    static uint32_t tmp[UINT32_ARRAY_SIZE];
    uint32_t prev = 0;
    for (int i = 0; i < sda_buffer.size; ++i) {
        if (sda_buffer.buf[i] == 0) {
            tmp[i] = prev;
        } else {
            prev = tmp[i] = sda_buffer.buf[i];
        }
    }
    return tmp;
}

// TODO: this should eventually go away.
void ez2c_master_process_buffers(void) {
    static int diff[UINT32_ARRAY_SIZE];
    int diff_size = 0;
    uint32_t diff_sum = 0;
    uint32_t *propagated_sda = propagate_sda_buffer();

    for (int i = 0; i < scl_buffer.size; ++i) {
        if (scl_buffer.buf[i]) {
            diff[diff_size] = (int)scl_buffer.buf[i] - (int)propagated_sda[i];
            diff_sum += diff[diff_size];
            diff_size++;
        }
    }

    float diff_avg = (float)diff_sum / (float)diff_size;
    printf("avg: %f", diff_avg);
    if (diff_avg > SLAVE_INTERRUPT_RISE_TIME_DIFF_THRESHOLD) {
        printf("\n\n\n!!!!! intr detected !!!!!\n");
        slave_interrupt_pending = true;
    }
    
    // printf("scl buffer content:\n");
    // for (int i = 0; i < scl_buffer.size; ++i) {
    //     printf("%u ", scl_buffer.buf[i]);
    // }
    // printf("\n\n");

    // printf("sda buffer content:\n");
    // for (int i = 0; i < sda_buffer.size; ++i) {
    //     printf("%u ", sda_buffer.buf[i]);
    // }
    // printf("\n\n");
    
    // printf("propagated sda buffer content:\n");
    // for (int i = 0; i < UINT32_ARRAY_SIZE; ++i) {
    //     printf("%u ", propagated_sda[i]);
    // }
    // printf("\n\n");
    
    // printf("diff (length %d, avg %f):\n", diff_size, (double)diff_sum / diff_size);
    // for (int i = 0; i < diff_size; ++i) {
    //     printf("%d ", diff[i]);
    // }
    // printf("\n\n");
    
    uint32_array_clear(&scl_buffer);
    uint32_array_clear(&sda_buffer);
}

bool ez2c_master_get_slave_interrupt() {
    return slave_interrupt_pending;
}

void ez2c_master_clear_slave_interrupt() {
    for (int i = 0; i < EZ2C_SLAVES_MAX; ++i) {
        poll_slave_interrupt(addr_at_index(i));
    }
    slave_interrupt_pending = false;
}

// ----------------------- Helper Function Definitions ------------------------

static void init_global_variables() {
    first_stall_recovered = false;
    ref_safe_rise_cycles_set = false;
    ref_safe_rise_cycles = 0.0f;
    device_change_pending = false;
    device_change = false;
    curr_rise_count_limit = PIO_NORMAL_RISE_COUNT_LIMIT;

    // Set up recent PIO rise time buffer.
    circular_buffer_clear(&recent_rise_cycles);
    uint32_array_clear(&scl_buffer);
    uint32_array_clear(&sda_buffer);
}

static void init_pull_up_demux(const uint *_pull_up_demux_pins,
                               uint _pull_up_level_bits) {
    // Validate user input for the number of pull-up level bits.
    if (_pull_up_level_bits > NUM_PULL_UP_LEVELS_MAX) {
        printf(
            "init_pull_up_demux: (WARNING) truncating pull-up level bits to "
            "%d\n",
            NUM_PULL_UP_LEVELS_MAX);
        _pull_up_level_bits = NUM_PULL_UP_LEVELS_MAX;
    }

    pull_up_level_bits = _pull_up_level_bits;

    // Initialize GPIO pins for demux output.
    for (uint i = 0; i < pull_up_level_bits; ++i) {
        pull_up_demux_pins[i] = _pull_up_demux_pins[i];
        gpio_init(pull_up_demux_pins[i]);
        gpio_set_dir(pull_up_demux_pins[i], GPIO_OUT);
    }

    set_pullup_level(pull_up_level_max());
    pullup_adjusted = false;
}

static void pio_init_error_handler(int error) {
    if (error == 1) {
        printf("failed to setup pio");
    } else if (error == 2) {
        printf("failed to find available nvic irq for pio\n");
    }
}

static void init_pio_rise_time_cycle_counter(uint scl_lo_pin, uint scl_hi_pin,
                                             uint sda_lo_pin, uint sda_hi_pin) {
    int error1 = rise_time_noblock_init(
        scl_lo_pin, scl_hi_pin, &pio_scl_counter_irq_handler,
        &scl_pio_hw, &scl_sm);
    if (error1) pio_init_error_handler(error1);
    int error2 = rise_time_noblock_init(
        sda_lo_pin, sda_hi_pin, &pio_sda_counter_irq_handler,
        &sda_pio_hw, &sda_sm);
    if (error2) pio_init_error_handler(error2);
}

static uint init_i2c(i2c_inst_t *i2c, uint baudrate, uint sda_pin, uint scl_pin,
                     bool internal_pullup) {
    gpio_init(sda_pin);
    gpio_init(scl_pin);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);

    if (internal_pullup) {
        // Enable internal pull-up.
        gpio_pull_up(sda_pin);
        gpio_pull_up(scl_pin);
    } else {
        // Disable all pulls.
        gpio_disable_pulls(sda_pin);
        gpio_disable_pulls(scl_pin);
    }

    // Clear all available slave addresses.
    for (int i = 0; i < EZ2C_SLAVES_MAX; ++i) {
        addr_reserved[i] = false;
    }

    i2c_hw = i2c;
    return i2c_init(i2c_hw, baudrate);
}

static inline uint pull_up_levels() { return 1u << pull_up_level_bits; }

static inline uint pull_up_level_max() { return pull_up_levels() - 1; }

static void pio_scl_counter_irq_handler() {
    static const int PIO_IRQ_MAX = 4;
    for (int irq = 0; irq < PIO_IRQ_MAX; ++irq) {
        if (pio_interrupt_get(scl_pio_hw, irq)) {
            scl_irq_handler_helper(irq);
        }
    }
}

static void scl_irq_handler_helper(int irq) {
    switch (irq) {
        case 0: {
            // Normal rise time output received.
            uint32_t cycles = rise_time_noblock_get_cycles(scl_pio_hw, scl_sm);
            if (scl_buffer.size < curr_rise_count_limit) {
                uint32_array_push_back(&scl_buffer, cycles);
                uint32_array_push_back(&sda_buffer, 0);
            }
            break;
        }

        case 1:
            printf("scl_irq_handler_helper: resolution warning\n");
            break;

        case 2:
            printf("scl_irq_handler_helper: capacitance warning\n");
            break;

        default:
            // NOT REACHED.
            printf("scl_irq_handler_helper: unknown irq flag warning\n");
            break;
    }

    // Clear PIO interrupt.
    pio_interrupt_clear(scl_pio_hw, irq);
}

static void pio_sda_counter_irq_handler() {
    static const int PIO_IRQ_MAX = 4;
    for (int irq = 0; irq < PIO_IRQ_MAX; ++irq) {
        if (pio_interrupt_get(sda_pio_hw, irq)) {
            sda_irq_handler_helper(irq);
        }
    }
}

static void sda_irq_handler_helper(int irq) {
    switch (irq) {
        case 0: {
            // Normal rise time output received.
            uint32_t cycles = rise_time_noblock_get_cycles(sda_pio_hw, sda_sm);
            if (scl_buffer.size < curr_rise_count_limit) {
                uint32_array_push_back(&sda_buffer, cycles);
                uint32_array_push_back(&scl_buffer, 0);
            }
            break;
        }

        case 1:
            printf("sda_irq_handler_helper: resolution warning\n");
            break;

        case 2:
            printf("sda_irq_handler_helper: capacitance warning\n");
            break;

        default:
            // NOT REACHED.
            printf(
                "sda_irq_handler_helper: unknown irq flag warning\n");
            break;
    }

    // Clear PIO interrupt.
    pio_interrupt_clear(sda_pio_hw, irq);
}

static bool adjust_pullup_conditional(float cycles) {
    // No adjustment can be made before the maximum safe rise time is
    // determined.
    if (!ref_safe_rise_cycles_set) return false;

    uint old_level = curr_pull_up_level;
    if (cycles > rise_cycles_control_max()) {
        // If the most recent rise time is longer than maximum allowed rise
        // time, tune pull-up resistance level down by 1 level. Return true if
        // adjusted, false otherwise.
        return old_level != adjust_pullup_level(-1);
    } else if (cycles < rise_cycles_control_min()) {
        // If the most recent rise time is shorter than minimum allowed rise
        // time, tune pull-up resistance level up by 1 level. Return true if
        // adjusted, false otherwise.
        return old_level != adjust_pullup_level(1);
    }

    // Not adjusted.
    return false;
}

// Sets pull-up resistance level to current level + OFFSET if the resulting
// level is valid and returns the new level. Does nothing and returns the
// current level otherwise.
static uint adjust_pullup_level(int offset) {
    uint new_level = curr_pull_up_level + offset;
    if (new_level > pull_up_level_max()) return curr_pull_up_level;

    printf(
        "adjust_pullup_level: adjusting pull up resistance level (%d -> %d)\n",
        curr_pull_up_level, new_level);
    return set_pullup_level(new_level);
}

// Sets pull-up resistance level to LEVEL and returns LEVEL.
// Assumes LEVEL is valid.
static uint set_pullup_level(uint level) {
    curr_pull_up_level = level;
    pullup_adjusted = true;
    for (uint i = 0; i < pull_up_level_bits; ++i) {
        gpio_put(pull_up_demux_pins[i], curr_pull_up_level & (1u << i));
    }
    return level;
}

static inline float rise_cycles_control_max() {
    return ref_safe_rise_cycles * SAFE_RISE_TIME_UPPER_BOUND_FACTOR;
}

static inline float rise_cycles_control_min() {
    return ref_safe_rise_cycles * SAFE_RISE_TIME_LOWER_BOUND_FACTOR;
}

static void detect_device_change(float new_avg_cycles, bool _pullup_adjusted) {
    if (_pullup_adjusted || !is_new_avg_cycles_stable(new_avg_cycles)) {
        // Unstable if pull-up resistance was recently adjusted, or if new cycle
        // measurement is outside of the stable range.
        printf(
            "detect_device_change: _pullup_adjusted == %d, instability "
            "detected\n",
            _pullup_adjusted);
        circular_buffer_clear(&recent_rise_cycles);
        circular_buffer_push(&recent_rise_cycles, new_avg_cycles);
        device_change_pending = true;
        return;
    }

    circular_buffer_push(&recent_rise_cycles, new_avg_cycles);
    printf(
        "detect_device_change: device_change_pending == %d, "
        "recent_rise_cycles.size = %d\n",
        device_change_pending, recent_rise_cycles.size);

    if (device_change_pending && recent_rise_cycles.size >= 4 &&
        is_recent_stable()) {
        device_change_pending = false;
        device_change = true;
        printf("detect_device_change: stablized\n");

        // If this is the first time we reach a stable state after the first
        // stall recovery, set current average rise time as the safe reference
        // rise time.
        if (!ref_safe_rise_cycles_set && first_stall_recovered) {
            ref_safe_rise_cycles = new_avg_cycles;
            ref_safe_rise_cycles_set = true;
        }
    }
}

static bool is_new_avg_cycles_stable(float cycles) {
    float avg = circular_buffer_get_avg(&recent_rise_cycles);
    float upper = avg + RISE_TIME_CYCLES_STABLE_THRESHOLD;
    float lower = avg - RISE_TIME_CYCLES_STABLE_THRESHOLD;
    return (cycles < upper && cycles > lower);
}

static bool is_recent_stable() {
    float avg = circular_buffer_get_avg(&recent_rise_cycles);
    float upper = avg + RISE_TIME_CYCLES_STABLE_THRESHOLD;
    float lower = avg - RISE_TIME_CYCLES_STABLE_THRESHOLD;
    for (int i = 0; i < recent_rise_cycles.size; ++i) {
        if (recent_rise_cycles.buf[i] >= upper ||
            recent_rise_cycles.buf[i] <= lower) {
            return false;
        }
    }
    return true;
}

static bool discover_slave() {
    uint8_t command = COMMAND_DISCOVER;
    printf(
        "discover_slave: scanning default slave address (0x%x) for new "
        "devices\n",
        I2C_DEFAULT_SLAVE_ADDR);
    int bytes_sent = ez2c_master_write_timeout_ms(
        I2C_DEFAULT_SLAVE_ADDR, &command, 1, false, I2C_DEFAULT_TIMEOUT_MS);
    if (bytes_sent == 1) {
        // at least one slave device got the command
        pico_unique_board_id_t id;
        ez2c_master_read_timeout_ms(I2C_DEFAULT_SLAVE_ADDR, &id, sizeof(id),
                                    false, I2C_DEFAULT_TIMEOUT_MS);
        return assign_slave_addr(id);
    }
    return false;
}

static bool assign_slave_addr(pico_unique_board_id_t id) {
    printf("assigning address for id %llx\n", *(uint64_t *)&id);
    uint8_t addr = reserve_next_addr();
    if (addr == (uint8_t)-1) {
        printf("assign: max address reached\n");
        return false;
    }

    printf("Assigning %x as the new slave address\n", addr);
    // Format: [address reassignment command | unique identifier | new address]
    uint8_t buf[2 + sizeof(pico_unique_board_id_t)];
    buf[0] = COMMAND_ASSIGN;
    memcpy(buf + 1, &id, sizeof(id));
    buf[1 + sizeof(pico_unique_board_id_t)] = addr;

    int bytes_sent =
        ez2c_master_write_timeout_ms(I2C_DEFAULT_SLAVE_ADDR, buf, sizeof(buf),
                                     false, I2C_DEFAULT_TIMEOUT_MS);
    return true;
}

static uint8_t reserve_next_addr() {
    int i = 0;
    while (addr_reserved[i] && i < EZ2C_SLAVES_MAX) {
        ++i;
    }
    if (i == EZ2C_SLAVES_MAX) return -1;

    addr_reserved[i] = true;
    return addr_at_index(i);
}

static inline uint8_t addr_at_index(int i) {
    return i + I2C_DEFAULT_SLAVE_ADDR + 1;
}

static bool poll_slave_interrupt(uint8_t addr) {
    uint8_t command = COMMAND_GET_INTERRUPT;
    int bytes_sent = ez2c_master_write_timeout_ms(addr, &command, 1, false,
                                 I2C_DEFAULT_TIMEOUT_MS);
    if (bytes_sent != 1) return false;
    
    printf("poll_slave_interrupt: scanning slave address 0x%x for interrupt\n",
           addr);

    uint8_t buf[1 + sizeof(pico_unique_board_id_t)];
    ez2c_master_read_timeout_ms(addr, &buf, sizeof(buf), false,
                                I2C_DEFAULT_TIMEOUT_MS);
    if (!(bool)(buf[0])) return false;

    // Grab slave's id and print it.
    printf("poll_slave_interrupt: recieved id from slave %llx\n", *(uint64_t *)(buf + 1));

    command = COMMAND_CLEAR_INTERRUPT;
    printf("poll_slave_interrupt: clearing interrupt at 0x%x...\n",
           addr);
    ez2c_master_write_timeout_ms(addr, &command, 1, false,
                                 I2C_DEFAULT_TIMEOUT_MS);
    return true;
}

static void stall_handler(uint8_t slave_addr) {
    uint8_t buf[STALL_RECOVERY_NUM_TEST_BYTES];
    int bytes_read = 0;
    bool read_success = false;

    while (!read_success) {
        // Reset pull-up adjusted flag and monitor pull-up changes.
        pullup_adjusted = false;
        bytes_read =
            i2c_read_timeout_us(i2c_hw, slave_addr, buf, sizeof(buf), false,
                                I2C_DEFAULT_TIMEOUT_MS * US_PER_MS);
        printf(
            "stall_handler: slave_addr: %x, bytes_read == %d, pullup_adjusted "
            "== %d\n",
            slave_addr, bytes_read, pullup_adjusted);
        read_success = (bytes_read == sizeof(buf));
        if (read_success) break;

        // If we can still do partial reads, keep reading and let dynamic
        // resistance adjustment routine do its job. If not a single byte
        // can be sent, iterate through all available pullup resistances.
        bool partial_success =
            (bytes_read >= 0 && bytes_read < sizeof(buf)) || pullup_adjusted;
        if (!partial_success) step_pullup_level();
    }
    // Read was successful. We can now return to normal operation.
    // Once we successfully recovered from the first I2C stall, we are ready
    // to set the maximum safe rise time. Note that this assumes the subsequent
    // rise time measurement corresponds to successful I2C communications.
    first_stall_recovered = true;
}

static uint8_t step_pullup_level() {
    static bool increasing = false;
    if (increasing && curr_pull_up_level >= pull_up_level_max()) {
        increasing = false;
    }
    if (!increasing && curr_pull_up_level <= 0) {
        increasing = true;
    }
    if (increasing) {
        set_pullup_level(++curr_pull_up_level);
    } else {
        set_pullup_level(--curr_pull_up_level);
    }
    printf("step_pullup_level: adjusting resistance level to %u\n",
           curr_pull_up_level);
    return curr_pull_up_level;
}
