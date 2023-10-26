#ifndef _BLINK2_MAIN_H
#define _BLINK2_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_849885723_H
#define TOP_LEVEL_PREAMBLE_849885723_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#endif
typedef struct {
    struct self_base_t base;
    
    #line 23 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink2.lf"
    bool led_on;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink2.lf"
    reaction_t _lf__reaction_0;
    #line 31 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink2.lf"
    reaction_t _lf__reaction_1;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink2.lf"
    trigger_t _lf__t;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink2.lf"
    reaction_t* _lf__t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _blink2_main_main_self_t;
_blink2_main_main_self_t* new__blink2_main();
#endif // _BLINK2_MAIN_H
