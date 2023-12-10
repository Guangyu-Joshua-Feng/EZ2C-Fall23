#pragma once

#include <hardware/i2c.h>
#include <pico/stdlib.h>

int guarded_i2c_write_timeout_ms(i2c_inst_t *i2c, uint8_t addr,
                                 const uint8_t *src, size_t len, bool nostop,
                                 uint timeout_ms);

int guarded_i2c_read_timeout_ms(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst,
                                size_t len, bool nostop, uint timeout_ms);
