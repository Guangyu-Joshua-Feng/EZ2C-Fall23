#ifndef _i2cdetection_main_H
#define _i2cdetection_main_H
#ifndef TOP_LEVEL_PREAMBLE_1459619729_H
#define TOP_LEVEL_PREAMBLE_1459619729_H
/*Correspondence: Range: [(10, 2), (19, 34)) -> Range: [(0, 0), (9, 34)) (verbatim=true; src=/home/ee149/EZ2C-Fall23/lf-3pi/src/I2cDetection.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <string.h>

#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/api.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct i2cdetection_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    bool master;
    int end[0]; // placeholder; MSVC does not compile empty structs
} i2cdetection_self_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_action_internal_t _base;
    self_base_t* parent;
    bool has_value;

    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} i2cdetection_send_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_action_internal_t _base;
    self_base_t* parent;
    bool has_value;

    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} i2cdetection_feedback_t;
#endif
