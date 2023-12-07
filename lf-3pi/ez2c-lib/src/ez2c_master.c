#include "ez2c_master.h"

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>
#include <pico/unique_id.h>

#include "circular_buffer.h"
#include "common.h"
#include "rise_time.h"

#define STALL_RECOVERY_NUM_TEST_BYTES 32
#define NUM_PULL_UP_LEVELS_MAX 8

static const uint I2C_DEFAULT_TIMEOUT_MS = 1000u;
static const uint PIO_NORMAL_RISE_COUNT_LIMIT = 1000u;
static const uint PIO_RECOVERY_RISE_COUNT_LIMIT = 16u;
static const float RISE_TIME_CYCLES_STABLE_THRESHOLD = 5.0f;
static const float SAFE_RISE_TIME_LOWER_BOUND_FACTOR = 0.8f;
static const float SAFE_RISE_TIME_UPPER_BOUND_FACTOR = 1.01f;

static i2c_inst_t *i2c_hw;  // I2C hardware in use as master.
static PIO pio_hw;          // PIO hardware in use for rise time cycle counter.
static uint sm;  // PIO state machine number for rise time cycle counter.

// PIO rise count limit currently in use.
static uint curr_pio_rise_count_limit;

static bool addr_reserved[EZ2C_SLAVES_MAX];

static bool first_stall_recovered;
static bool ref_safe_rise_cycles_set;
static float ref_safe_rise_cycles;

static void init_global_variables(const uint *_pull_up_demux_pins,
                                  uint _pull_up_level_bits);
static void init_pio_rise_time_cycle_counter(uint lo_pin, uint hi_pin);
static void pio_counter_irq_handler();
static void pio_irq_handler_helper(int i);

static bool discover_slave();
static bool assign_slave_addr(pico_unique_board_id_t id);
static uint8_t reserve_next_addr();
static inline uint8_t addr_at_index(int i);

static bool adjust_pullup_conditional(float cycles);
static uint set_pullup_level(uint level);
static uint adjust_pullup_level(int offset);
static void detect_device_change(float new_avg_cycles, bool pullup_adjusted);
static bool is_new_avg_cycles_stable(float cycles);
static bool is_recent_stable();
static void stall_handler(uint8_t slave_addr);

static uint8_t pull_up_level_bits;
static uint curr_pullup_level;
static bool pullup_adjusted;
static uint pull_up_demux_pins[NUM_PULL_UP_LEVELS_MAX];

static inline uint pull_up_levels();
static inline uint pull_up_level_max();

static circular_buffer_t recent_rise_cycles;
static bool device_change_pending;
static bool device_change;

static inline float rise_cycles_control_max();
static inline float rise_cycles_control_min();

// -----------------------------------------------------------------------------

uint ez2c_master_init(i2c_inst_t *i2c, uint baudrate, uint sda_pin,
                      uint scl_pin, uint timeout_ms, uint pio_lo_pin,
                      uint pio_hi_pin, const uint *_pull_up_demux_pins,
                      uint _pull_up_level_bits, bool internal_pullup) {
    static bool once = false;
    if (!once) {
        once = true;
    } else {
        printf(
            "ez2c_master_init: (WARNING) master already initialized, "
            "aborting...\n");
        return 0;
    }

    init_global_variables(_pull_up_demux_pins, _pull_up_level_bits);
    init_pio_rise_time_cycle_counter(pio_lo_pin, pio_hi_pin);

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

    // Clear all available addresses.
    for (int i = 0; i < EZ2C_SLAVES_MAX; ++i) {
        addr_reserved[i] = false;
    }

    i2c_hw = i2c;
    return i2c_init(i2c_hw, baudrate);
}

int ez2c_master_discover() {
    int count = 0;
    bool discovered = true;

    while (discovered) {
        discovered = discover_slave();
        count += discovered;
    }

    return count;
}

bool ez2c_get_device_change() { return device_change; }

void ez2c_clear_device_change() { device_change = false; }

int ez2c_master_write_timeout_ms(uint8_t addr, const uint8_t *src, size_t len,
                                 bool nostop, uint timeout_ms) {
    int bytes_written = i2c_write_timeout_us(i2c_hw, addr, src, len, nostop,
                                             timeout_ms * US_PER_MS);

    // A timeout likely indicates that the pullup resistance is incorrectly set.
    while (bytes_written == PICO_ERROR_TIMEOUT) {
        // Initiate recovery subroutine.
        stall_handler(addr);
        // Retry I2C write.
        bytes_written = i2c_write_timeout_us(i2c_hw, addr, src, len, nostop,
                                             timeout_ms * US_PER_MS);
    }
    return bytes_written;
}

int ez2c_master_read_timeout_ms(uint8_t addr, uint8_t *dst, size_t len,
                                bool nostop, uint timeout_ms) {
    int bytes_read = i2c_read_timeout_us(i2c_hw, addr, dst, len, nostop,
                                         timeout_ms * US_PER_MS);
    // A timeout likely indicates that the pullup resistance is incorrectly set.
    while (bytes_read == PICO_ERROR_TIMEOUT) {
        // Initiate recovery subroutine.
        stall_handler(addr);
        // Retry I2C read.
        bytes_read = i2c_read_timeout_us(i2c_hw, addr, dst, len, nostop,
                                         timeout_ms * US_PER_MS);
    }
    return bytes_read;
}

// -----------------------------------------------------------------------------

static void init_global_variables(const uint *_pull_up_demux_pins,
                                  uint _pull_up_level_bits) {
    curr_pio_rise_count_limit = PIO_NORMAL_RISE_COUNT_LIMIT;
    first_stall_recovered = false;
    ref_safe_rise_cycles_set = false;
    ref_safe_rise_cycles = 0.0f;
    device_change_pending = false;
    device_change = false;

    // Set up pull-up demux.
    pull_up_level_bits = _pull_up_level_bits;
    curr_pullup_level = pull_up_level_max();
    if (_pull_up_demux_pins > NUM_PULL_UP_LEVELS_MAX) {
        printf(
            "init_global_variables: (WARNING) truncating pull-up level bits to "
            "%d\n",
            NUM_PULL_UP_LEVELS_MAX);
        _pull_up_level_bits = NUM_PULL_UP_LEVELS_MAX;
    }
    for (uint i = 0; i < _pull_up_level_bits; ++i) {
        pull_up_demux_pins[i] = _pull_up_demux_pins[i];
    }
    pullup_adjusted = false;

    // Set up recent PIO rise time buffer.
    circular_buffer_clear(&recent_rise_cycles);
}

static void init_pio_rise_time_cycle_counter(uint lo_pin, uint hi_pin) {
    rise_time_init(lo_pin, hi_pin, PIO_NORMAL_RISE_COUNT_LIMIT,
                   &pio_counter_irq_handler, &pio_hw, &sm);
}

static void pio_counter_irq_handler() {
    static const int PIO_IRQ_MAX = 4;
    for (int irq = 0; irq < PIO_IRQ_MAX; ++irq) {
        if (pio_interrupt_get(pio_hw, irq)) {
            pio_irq_handler_helper(irq);
        }
    }
}

static void pio_irq_handler_helper(int irq) {
    switch (irq) {
        case 0: {
            float avg_cycles =
                get_avg_cycles(pio_hw, sm, curr_pio_rise_count_limit);
            printf("pio_irq_handler_helper: %f cycles\n", avg_cycles);
            bool adjusted = adjust_pullup_conditional(avg_cycles);
            detect_device_change(avg_cycles, adjusted);
            pio_sm_put_blocking(pio_hw, sm, curr_pio_rise_count_limit - 1);
            break;
        }

        case 1:
            printf("pio_irq_handler_helper: resolution warning\n");
            break;

        case 2:
            printf("pio_irq_handler_helper: capacitance warning\n");
            // TODO: decrease pullup here
            break;

        default:
            printf("pio_irq_handler_helper: unknown irq flag warning\n");
            break;
    }
    pio_interrupt_clear(pio_hw, irq);
}

static bool adjust_pullup_conditional(float cycles) {
    // No adjustment can be made before the maximum safe rise time is
    // determined.
    if (!ref_safe_rise_cycles_set) return false;

    uint old_level = curr_pullup_level;
    if (cycles > rise_cycles_control_max()) {
        // True if adjusted, false otherwise.
        return old_level != adjust_pullup_level(-1);
    } else if (cycles < rise_cycles_control_min()) {
        // True if adjusted, false otherwise.
        return old_level != adjust_pullup_level(1);
    }

    // Not adjusted.
    return false;
}

static uint set_pullup_level(uint level) {
    curr_pullup_level = level;
    pullup_adjusted = true;
    for (uint i = 0; i < pull_up_level_bits; ++i) {
        gpio_put(pull_up_demux_pins[i], curr_pullup_level & (1u << i));
    }
    return level;
}

static uint adjust_pullup_level(int offset) {
    uint new_level = curr_pullup_level + offset;
    if (new_level > pull_up_level_max()) return curr_pullup_level;

    printf(
        "adjust_pullup_level: adjusting pull up resistance level (%d -> %d)\n",
        curr_pullup_level, new_level);
    return set_pullup_level(new_level);
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
        if (!ref_safe_rise_cycles_set && first_stall_recovered) {
            ref_safe_rise_cycles = new_avg_cycles;
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

static void stall_handler(uint8_t slave_addr) {
    uint8_t buf[STALL_RECOVERY_NUM_TEST_BYTES];
    int bytes_read = 0;
    bool read_success = false;

    while (!read_success) {
        // Reset PIO cycle counter limit to a small value and restart state
        // machine.
        curr_pio_rise_count_limit = PIO_RECOVERY_RISE_COUNT_LIMIT;
        rise_time_reset_rise_count_limit(pio_hw, sm, curr_pio_rise_count_limit);

        // Reset pull-up adjusted flag and monitor pull-up changes.
        pullup_adjusted = false;
        bytes_read =
            i2c_read_timeout_us(i2c_hw, slave_addr, buf, sizeof(buf), false,
                                I2C_DEFAULT_TIMEOUT_MS * US_PER_MS);
        printf("stall_handler: bytes_read == %d, pullup_adjusted == %d\n",
               bytes_read, pullup_adjusted);
        read_success = (bytes_read == sizeof(buf));
        if (read_success) break;

        // If we can still do partial reads, keep reading and let dynamic
        // resistance adjustment routine do its job. If not a single byte
        // can be sent, iterate through all available pullup resistances.
        bool partial_success =
            (bytes_read >= 0 && bytes_read < sizeof(buf)) || pullup_adjusted;
        if (!partial_success) step_pullup_resistance_level();
    }

    // Read was successful. We can now return to normal operation.
    curr_pio_rise_count_limit = PIO_NORMAL_RISE_COUNT_LIMIT;
    rise_time_reset_rise_count_limit(pio_hw, sm, curr_pio_rise_count_limit);

    // Once we successfully recovered from the first I2C stall, we are ready
    // to set the maximum safe rise time. Note that this assumes the subsequent
    // rise time measurement corresponds to successful I2C communications.
    first_stall_recovered = true;
}

static inline uint pull_up_levels() { return 1u << pull_up_level_bits; }

static inline uint pull_up_level_max() { return pull_up_levels() - 1; }

static inline float rise_cycles_control_max() {
    return ref_safe_rise_cycles * SAFE_RISE_TIME_UPPER_BOUND_FACTOR;
}

static inline float rise_cycles_control_min() {
    return ref_safe_rise_cycles * SAFE_RISE_TIME_LOWER_BOUND_FACTOR;
}
