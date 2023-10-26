#ifndef _blink_main_H
#define _blink_main_H
#ifndef TOP_LEVEL_PREAMBLE_1894287849_H
#define TOP_LEVEL_PREAMBLE_1894287849_H
/*Correspondence: Range: [(15, 2), (20, 14)) -> Range: [(0, 0), (5, 14)) (verbatim=true; src=/home/foobar/EZ2C-Fall23/lf-3pi/src/Blink.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

#define SDA 7
#define SCL 24
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
