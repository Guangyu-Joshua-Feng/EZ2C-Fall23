#ifndef _BLINK_FEDERATED_MAIN_H
#define _BLINK_FEDERATED_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_1894287849_H
#define TOP_LEVEL_PREAMBLE_1894287849_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#endif
typedef struct {
    struct self_base_t base;
    
    #line 23 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    bool led_on;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    reaction_t _lf__reaction_0;
    #line 32 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    reaction_t _lf__reaction_1;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    trigger_t _lf__t;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    reaction_t* _lf__t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _blink_federated_main_main_self_t;
_blink_federated_main_main_self_t* new__blink_federated_main();
#endif // _BLINK_FEDERATED_MAIN_H
