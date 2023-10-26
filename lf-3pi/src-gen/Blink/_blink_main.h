#ifndef _BLINK_MAIN_H
#define _BLINK_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_1894287849_H
#define TOP_LEVEL_PREAMBLE_1894287849_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

#define SDA 7
#define SCL 24
#endif
typedef struct {
    struct self_base_t base;
    
    #line 26 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink.lf"
    bool led_on;
    #line 28 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink.lf"
    reaction_t _lf__reaction_0;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink.lf"
    reaction_t _lf__reaction_1;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink.lf"
    trigger_t _lf__t;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink.lf"
    reaction_t* _lf__t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _blink_main_main_self_t;
_blink_main_main_self_t* new__blink_main();
#endif // _BLINK_MAIN_H
