#ifndef _circularslave_main_H
#define _circularslave_main_H
#ifndef TOP_LEVEL_PREAMBLE_922871524_H
#define TOP_LEVEL_PREAMBLE_922871524_H
/*Correspondence: Range: [(11, 2), (26, 22)) -> Range: [(0, 0), (15, 22)) (verbatim=true; src=/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/unique_id.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <string.h>

#define INTERNAL_PULL_UP 1
#define I2C_DEFAULT_SLAVE_ADDR 0x55
#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5

#define COMMAND_DISCOVER 0
#define COMMAND_ASSIGN 1
#define COMMAND_ECHO 2
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/api.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct circularslave_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    int end[0]; // placeholder; MSVC does not compile empty structs
} circularslave_self_t;
#endif
