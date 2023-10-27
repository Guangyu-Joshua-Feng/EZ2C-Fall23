#ifndef _I2CMASTER_MAIN_H
#define _I2CMASTER_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_368242083_H
#define TOP_LEVEL_PREAMBLE_368242083_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <hardware/i2c.h>

#define ADDR 0x55
#define i2c_default i2c0
#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5
#endif
typedef struct {
    struct self_base_t base;
    
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    bool led_on;
    #line 27 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    reaction_t _lf__reaction_0;
    #line 42 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    reaction_t _lf__reaction_1;
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    trigger_t _lf__t;
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    reaction_t* _lf__t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _i2cmaster_main_main_self_t;
_i2cmaster_main_main_self_t* new__i2cmaster_main();
#endif // _I2CMASTER_MAIN_H
