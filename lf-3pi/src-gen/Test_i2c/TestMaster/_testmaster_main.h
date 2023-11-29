#ifndef _TESTMASTER_MAIN_H
#define _TESTMASTER_MAIN_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_924393200_H
#define TOP_LEVEL_PREAMBLE_924393200_H
#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/unique_id.h>
#include <string.h>

#define MAX_SLAVES 30
#define INTERNAL_PULL_UP 1
#define I2C_DEFAULT_SLAVE_ADDR 0x55
#define PICO_DEFAULT_I2C_SDA_PIN 4
#define PICO_DEFAULT_I2C_SCL_PIN 5

#define COMMAND_DISCOVER 0
#define COMMAND_ASSIGN 1
#define COMMAND_ECHO 2
#endif
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
} _testmaster_main_button_t;
typedef struct {
    struct self_base_t base;
    
    #line 134 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    bool discover_done;
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    _testmaster_main_button_t _lf_button;
    #line 139 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    reaction_t _lf__reaction_0;
    #line 145 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    reaction_t _lf__reaction_1;
    #line 152 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    reaction_t _lf__reaction_2;
    #line 160 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    reaction_t _lf__reaction_3;
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    trigger_t _lf__button_scan_t;
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    reaction_t* _lf__button_scan_t_reactions[1];
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    trigger_t _lf__echo_t;
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    reaction_t* _lf__echo_t_reactions[1];
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    trigger_t _lf__button;
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    reaction_t* _lf__button_reactions[1];
} _testmaster_main_main_self_t;
_testmaster_main_main_self_t* new__testmaster_main();
#endif // _TESTMASTER_MAIN_H
