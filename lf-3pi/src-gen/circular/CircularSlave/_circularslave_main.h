#ifndef _CIRCULARSLAVE_MAIN_H
#define _CIRCULARSLAVE_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_922871524_H
#define TOP_LEVEL_PREAMBLE_922871524_H
#include <stdio.h>
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
typedef struct {
    struct self_base_t base;
    
    
    #line 116 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    reaction_t _lf__reaction_0;
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _circularslave_main_main_self_t;
_circularslave_main_main_self_t* new__circularslave_main();
#endif // _CIRCULARSLAVE_MAIN_H
