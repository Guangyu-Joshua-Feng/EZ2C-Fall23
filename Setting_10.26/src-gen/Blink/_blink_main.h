#ifndef _BLINK_MAIN_H
#define _BLINK_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_368242083_H
#define TOP_LEVEL_PREAMBLE_368242083_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#endif
typedef struct {
    struct self_base_t base;
    
    #line 25 "/home/foobar/lf-3pi-Jiahui-Cheng/src/Blink.lf"
    bool led_on;
    #line 27 "/home/foobar/lf-3pi-Jiahui-Cheng/src/Blink.lf"
    reaction_t _lf__reaction_0;
    #line 31 "/home/foobar/lf-3pi-Jiahui-Cheng/src/Blink.lf"
    reaction_t _lf__reaction_1;
    #line 24 "/home/foobar/lf-3pi-Jiahui-Cheng/src/Blink.lf"
    trigger_t _lf__t;
    #line 24 "/home/foobar/lf-3pi-Jiahui-Cheng/src/Blink.lf"
    reaction_t* _lf__t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
} _blink_main_main_self_t;
_blink_main_main_self_t* new__blink_main();
#endif // _BLINK_MAIN_H
