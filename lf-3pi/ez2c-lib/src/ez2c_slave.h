#pragma once

#include <pico/i2c_slave.h>
#include <pico/stdlib.h>

uint ez2c_slave_init(i2c_inst_t *i2c, uint baudrate, uint sda_pin, uint scl_pin,
                     uint led_pin, bool internal_pullup);
