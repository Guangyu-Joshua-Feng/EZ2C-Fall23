#ifndef _I2CSLAVE_MAIN_H
#define _I2CSLAVE_MAIN_H
#include "include/core/reactor.h"
#include "_display.h"
#ifndef TOP_LEVEL_PREAMBLE_179441020_H
#define TOP_LEVEL_PREAMBLE_179441020_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>

#define ADDR 0x55
#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5
#define I2C_MASTER_SDA_PIN  6
#define I2C_MASTER_SCL_PIN  7
#include <pico/stdlib.h>
#include <display.h>        // Do not use "display.h". Doesn't work.
#endif
typedef struct {
    struct self_base_t base;
    
    #line 99 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    bool led_on;
    #line 101 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    reaction_t _lf__reaction_0;
    #line 113 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    reaction_t _lf__reaction_1;
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    trigger_t _lf__t;
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    reaction_t* _lf__t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _i2cslave_main_main_self_t;
_i2cslave_main_main_self_t* new__i2cslave_main();
#endif // _I2CSLAVE_MAIN_H
