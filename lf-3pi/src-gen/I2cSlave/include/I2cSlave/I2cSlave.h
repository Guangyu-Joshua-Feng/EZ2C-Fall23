#ifndef _i2cslave_main_H
#define _i2cslave_main_H
#ifndef TOP_LEVEL_PREAMBLE_577629452_H
#define TOP_LEVEL_PREAMBLE_577629452_H
/*Correspondence: Range: [(9, 2), (14, 17)) -> Range: [(0, 0), (5, 17)) (verbatim=true; src=/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>

#define ADDR 0x55
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/api.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct i2cslave_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    bool led_on;
    int end[0]; // placeholder; MSVC does not compile empty structs
} i2cslave_self_t;
#endif
