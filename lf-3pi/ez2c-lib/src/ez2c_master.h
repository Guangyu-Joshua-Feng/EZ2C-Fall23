#pragma once

#include <hardware/i2c.h>
#include <pico/stdlib.h>

#define EZ2C_SLAVES_MAX 30  // Maximum supported number of I2C slave devices.

/**
 * @brief Initializes the given I2C hardware block as an I2C master.
 *
 * @param i2c I2C hardware block to initialize.
 * @param baudrate Baudrate.
 * @param sda_pin SDA (data) pin number.
 * @param scl_pin SCL (clock) pin number.
 * @param pio_scl_lo_pin PIO rise time cycle counter scl line low threshold
 * input pin number.
 * @param pio_scl_hi_pin PIO rise time cycle counter scl line high threshold
 * input pin number.
 * @param pio_sda_lo_pin PIO rise time cycle counter sda line low threshold
 * input pin number.
 * @param pio_sda_hi_pin PIO rise time cycle counter sda line high threshold
 * input pin number.
 * @param pull_up_demux_pins An array of pull-up demux input pin numbers of size
 * PULL_UP_LEVEL_BITS.
 * @param pull_up_level_bits Number of bits used to represent one pull-up level.
 * @param internal_pullup Whether or not to use Pico's internal pull-up
 * resistors.
 * @param pio_noblock Whether or not to use non-blocking PIO cycle counters.
 *
 * @return Actual set baudrate.
 */
uint ez2c_master_init(i2c_inst_t *i2c, uint baudrate, uint sda_pin,
                      uint scl_pin, uint pio_scl_lo_pin, uint pio_scl_hi_pin,
                      uint pio_sda_lo_pin, uint pio_sda_hi_pin,
                      const uint *pull_up_demux_pins, uint pull_up_level_bits,
                      bool internal_pullup, bool pio_noblock);

/**
 * @brief Discovers new slave devices.
 *
 * @return Number of new devices discovered.
 */
int ez2c_master_discover();

bool ez2c_master_slave_addr_exists(uint8_t addr);

bool ez2c_get_device_change();

void ez2c_clear_device_change();

int ez2c_master_write_timeout_ms(uint8_t addr, const uint8_t *src, size_t len,
                                 bool nostop, uint timeout_ms);

int ez2c_master_read_timeout_ms(uint8_t addr, uint8_t *dst, size_t len,
                                bool nostop, uint timeout_ms);

void ez2c_master_print_buffers(void);
