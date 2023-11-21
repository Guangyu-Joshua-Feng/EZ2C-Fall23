#ifndef _TESTSLAVE_MAIN_H
#define _TESTSLAVE_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_1454456125_H
#define TOP_LEVEL_PREAMBLE_1454456125_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/unique_id.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <string.h>
#include <math.h>

#define INTERNAL_PULL_UP 1
#define I2C_DEFAULT_SLAVE_ADDR 0x55
#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5
#define ADDR_BIT_NUM 4

#define COMMAND_DISCOVER 0
#define COMMAND_ASSIGN 1
#define COMMAND_ECHO 2
#endif
typedef struct {
    struct self_base_t base;
    
    
    #line 138 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestSlave.lf"
    reaction_t _lf__reaction_0;
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _testslave_main_main_self_t;
_testslave_main_main_self_t* new__testslave_main();
#endif // _TESTSLAVE_MAIN_H
