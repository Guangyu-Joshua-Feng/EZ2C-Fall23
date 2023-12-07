#include <hardware/i2c.h>
#include <i2c_utils.h>
#include <pico/stdlib.h>
#include <rise_time.h>

int guarded_i2c_write_timeout_ms(i2c_inst_t *i2c, uint8_t addr,
                                 const uint8_t *src, size_t len, bool nostop,
                                 uint timeout_ms) {}

int guarded_i2c_read_timeout_ms(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst,
                                size_t len, bool nostop, uint timeout_ms) {
    int bytes_read = i2c_read_timeout_us(i2c, addr, dst, len, nostop,
                                         timeout_ms * us_per_ms);
    // A timeout likely indicates that the pullup resistance is incorrectly set.
    while (bytes_read == PICO_ERROR_TIMEOUT) {
        // Initiate recovery subroutine.
        i2c_stall_handler(addr);
        // Retry I2C read.
        bytes_read = i2c_read_timeout_us(i2c, addr, dst, len, nostop,
                                         timeout_ms * us_per_ms);
    }
    return bytes_read;
}

static void i2c_stall_handler(uint8_t slave_addr) {
    uint8_t buf[2];
    int bytes_read = 0;
    bool read_success = false;

    max_safe_rise_cycles_set = true;
    while (!read_success) {
        // Reset PIO cycle counter limit to a small value and restart state
        // machine.
        rise_count_limit = RISE_TIME_RECOVERY_COUNT_LIMIT;
        rise_time_reset_rise_count_limit(pio_hw, sm, rise_count_limit);
        pullup_adjusted = false;
        bytes_read =
            i2c_read_timeout_us(i2c0, slave_addr, buf, sizeof(buf), false,
                                I2C_DEFAULT_TIMEOUT_MS * us_per_ms);
        printf("i2c_stall_handler: bytes_read == %d, pullup_adjusted == %d\n",
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
}
