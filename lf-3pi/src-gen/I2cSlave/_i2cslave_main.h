#ifndef _I2CSLAVE_MAIN_H
#define _I2CSLAVE_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_577629452_H
#define TOP_LEVEL_PREAMBLE_577629452_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>

#define ADDR 0x55
#endif
typedef struct {
    struct self_base_t base;
    
    #line 20 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    bool led_on;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    reaction_t _lf__reaction_0;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    reaction_t _lf__reaction_1;
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    trigger_t _lf__t;
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    reaction_t* _lf__t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _i2cslave_main_main_self_t;
_i2cslave_main_main_self_t* new__i2cslave_main();
#endif // _I2CSLAVE_MAIN_H
