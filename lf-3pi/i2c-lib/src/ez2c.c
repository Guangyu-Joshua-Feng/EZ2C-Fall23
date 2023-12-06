#include <ez2c.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>
#include <pico/unique_id.h>
#include <rise_time.h>

#define MAX_SLAVES 30  // Maximum supported number of I2C slave devices.

static const uint US_PER_MS = 1000;
static const uint8_t COMMAND_DISCOVER = 0;
static const uint8_t COMMAND_ASSIGN = 1;
static const uint8_t COMMAND_ECHO = 2;
static const uint8_t I2C_DEFAULT_SLAVE_ADDR = 0x55;

static uint i2c_default_timeout_ms = 1000;
static bool registered_addresses[MAX_SLAVES];

static bool first_stall_recovered = false;
static bool max_safe_rise_cycles_set = false;
static float max_safe_rise_cycles = 0.0f;

static void init_global_variables();

static bool discover_slave();
static void assign_slave_addr(pico_unique_board_id_t id);
static uint8_t reserve_next_addr();
static inline uint8_t addr_at_index(int i);
static void stall_handler(uint8_t slave_addr);

// -----------------------------------------------------------------------------

int ez2c_init_master(i2c_inst_t *i2c, uint baud, uint sda, uint scl,
                     uint default_timeout_ms, bool internal_pullup) {
    init_global_variables();
    gpio_init(sda);
    gpio_init(scl);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    if (internal_pullup) {
        gpio_pull_up(sda);
        gpio_pull_up(scl);
    } else {
        gpio_disable_pulls(sda);
        gpio_disable_pulls(scl);
    }
    i2c_init(i2c, baud);
    i2c_default_timeout_ms = default_timeout_ms;
    for (int i = 0; i < MAX_SLAVES; ++i) {
        registered_addresses[i] = false;
    }
}

int ez2c_write_timeout_ms(i2c_inst_t *i2c, uint8_t addr, const uint8_t *src,
                          size_t len, bool nostop, uint timeout_ms) {
    int bytes_written = i2c_write_timeout_us(i2c, addr, src, len, nostop,
                                             timeout_ms * US_PER_MS);

    // A timeout likely indicates that the pullup resistance is incorrectly set.
    while (bytes_written == PICO_ERROR_TIMEOUT) {
        // Initiate recovery subroutine.
        stall_handler(addr);
        // Retry I2C write.
        bytes_written = i2c_write_timeout_us(i2c, addr, src, len, nostop,
                                             timeout_ms * US_PER_MS);
    }
    return bytes_written;
}

int ez2c_read_timeout_ms(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst,
                         size_t len, bool nostop, uint timeout_ms) {
    int bytes_read = i2c_read_timeout_us(i2c, addr, dst, len, nostop,
                                         timeout_ms * US_PER_MS);
    // A timeout likely indicates that the pullup resistance is incorrectly set.
    while (bytes_read == PICO_ERROR_TIMEOUT) {
        // Initiate recovery subroutine.
        stall_handler(addr);
        // Retry I2C read.
        bytes_read = i2c_read_timeout_us(i2c, addr, dst, len, nostop,
                                         timeout_ms * US_PER_MS);
    }
    return bytes_read;
}

// -----------------------------------------------------------------------------

static void init_global_variables() {
    i2c_default_timeout_ms = 1000;
    first_stall_recovered = false;
    max_safe_rise_cycles_set = false;
    max_safe_rise_cycles = 0.0f;
}

bool i2c_circular_addr_rescan() {
    bool discover_done = false;
    bool change = false;
    while (!discover_done) {
        bool discovered = discover_slave();
        change |= discovered;
        discover_done = !discovered;
    }
    return change;
}

static bool discover_slave() {
    uint8_t command = COMMAND_DISCOVER;
    printf(
        "discover_slave: scanning default slave address (0x%x) for new "
        "devices\n",
        I2C_DEFAULT_SLAVE_ADDR);
    int bytes_sent =
        ez2c_write_timeout_ms(i2c0, I2C_DEFAULT_SLAVE_ADDR, &command, 1, false,
                              i2c_default_timeout_ms);
    if (bytes_sent == 1) {
        // at least one slave device got the command
        pico_unique_board_id_t id;
        ez2c_read_timeout_ms(i2c0, I2C_DEFAULT_SLAVE_ADDR, &id, sizeof(id),
                             false, i2c_default_timeout_ms);
        assign_slave_addr(id);
        return true;
    } else {
        return false;
    }
}

static void assign_slave_addr(pico_unique_board_id_t id) {
    printf("assigning address for id %llx\n", *(uint64_t *)&id);
    uint8_t addr = reserve_next_addr();
    if (addr == (uint8_t)-1) {
        printf("assign: max address reached\n");
        return;
    }
    printf("Assigning %x as the new slave address\n", addr);

    // Format: [address reassignment command | unique identifier | new address]
    uint8_t buf[2 + sizeof(pico_unique_board_id_t)];
    buf[0] = COMMAND_ASSIGN;
    memcpy(buf + 1, &id, sizeof(id));
    buf[1 + sizeof(pico_unique_board_id_t)] = addr;

    int bytes_sent =
        ez2c_write_timeout_ms(i2c0, I2C_DEFAULT_SLAVE_ADDR, buf, sizeof(buf),
                              false, i2c_default_timeout_ms);
}

static uint8_t reserve_next_addr() {
    int i = 0;
    while (registered_addresses[i] && i < MAX_SLAVES) {
        ++i;
    }
    if (i == MAX_SLAVES) return -1;

    registered_addresses[i] = true;
    return addr_at_index(i);
}

static inline uint8_t addr_at_index(int i) {
    return i + I2C_DEFAULT_SLAVE_ADDR + 1;
}

static void stall_handler(uint8_t slave_addr) {
    uint8_t buf[2];
    int bytes_read = 0;
    bool read_success = false;

    while (!read_success) {
        // Reset PIO cycle counter limit to a small value and restart state
        // machine.
        rise_count_limit = RISE_TIME_RECOVERY_COUNT_LIMIT;
        rise_time_reset_rise_count_limit(pio_hw, sm, rise_count_limit);
        pullup_adjusted = false;
        bytes_read =
            i2c_read_timeout_us(i2c0, slave_addr, buf, sizeof(buf), false,
                                I2C_DEFAULT_TIMEOUT_MS * us_per_ms);
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

    // Read was complete and successful and we can return to normal operation.
    rise_count_limit = RISE_TIME_COUNT_LIMIT;
    rise_time_reset_rise_count_limit(pio_hw, sm, rise_count_limit);
    first_stall_recovered = true;
}
