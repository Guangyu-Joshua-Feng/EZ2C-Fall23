#ifndef _i2cslave1_main_H
#define _i2cslave1_main_H
#ifndef TOP_LEVEL_PREAMBLE_1099694603_H
#define TOP_LEVEL_PREAMBLE_1099694603_H
/*Correspondence: Range: [(10, 2), (20, 34)) -> Range: [(0, 0), (10, 34)) (verbatim=true; src=/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave1.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <string.h>

#define ADDR 0x55
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
typedef struct i2cslave1_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    bool LED;
    int end[0]; // placeholder; MSVC does not compile empty structs
} i2cslave1_self_t;
#endif
