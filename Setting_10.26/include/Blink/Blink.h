#ifndef _blink_main_H
#define _blink_main_H
#ifndef TOP_LEVEL_PREAMBLE_368242083_H
#define TOP_LEVEL_PREAMBLE_368242083_H
/*Correspondence: Range: [(16, 2), (19, 25)) -> Range: [(0, 0), (3, 25)) (verbatim=true; src=/home/foobar/lf-3pi-Jiahui-Cheng/src/Blink.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/api.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct blink_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    bool led_on;
    int end[0]; // placeholder; MSVC does not compile empty structs
} blink_self_t;
#endif
