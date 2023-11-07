#ifndef _i2ccircular1_main_H
#define _i2ccircular1_main_H
#ifndef TOP_LEVEL_PREAMBLE_1745701482_H
#define TOP_LEVEL_PREAMBLE_1745701482_H
/*Correspondence: Range: [(10, 2), (22, 34)) -> Range: [(0, 0), (12, 34)) (verbatim=true; src=/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cCircular1.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <string.h>

#define ADDR1 0x55
#define ADDR2 0x56
#define ADDR3 0x57
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
typedef struct i2ccircular1_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    int end[0]; // placeholder; MSVC does not compile empty structs
} i2ccircular1_self_t;
#endif
