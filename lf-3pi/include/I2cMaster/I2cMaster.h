#ifndef _i2cmaster_main_H
#define _i2cmaster_main_H
#ifndef TOP_LEVEL_PREAMBLE_368242083_H
#define TOP_LEVEL_PREAMBLE_368242083_H
/*Correspondence: Range: [(10, 2), (19, 34)) -> Range: [(0, 0), (9, 34)) (verbatim=true; src=/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <hardware/i2c.h>

#define ADDR 0x55
#define i2c_default i2c0
#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/api.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct i2cmaster_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    bool led_on;
    int end[0]; // placeholder; MSVC does not compile empty structs
} i2cmaster_self_t;
#endif
