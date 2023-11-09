#ifndef _i2cmaster_main_H
#define _i2cmaster_main_H
#ifndef TOP_LEVEL_PREAMBLE_1923241952_H
#define TOP_LEVEL_PREAMBLE_1923241952_H
/*Correspondence: Range: [(10, 2), (23, 22)) -> Range: [(0, 0), (13, 22)) (verbatim=true; src=/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf)*/#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/unique_id.h>
#include <string.h>

#define I2C_DEFAULT_SLAVE_ADDR 0x55
#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5

#define COMMAND_DISCOVER 0
#define COMMAND_ASSIGN 1
#define COMMAND_ECHO 2
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/api.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct i2cmaster_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    bool discover_done;
    bool LED;
    int end[0]; // placeholder; MSVC does not compile empty structs
} i2cmaster_self_t;
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
} i2cmaster_button_t;
#endif
