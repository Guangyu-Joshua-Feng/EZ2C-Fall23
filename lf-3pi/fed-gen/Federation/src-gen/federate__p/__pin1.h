#ifndef __PIN1_H
#define __PIN1_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_1096884346_H
#define TOP_LEVEL_PREAMBLE_1096884346_H
#ifdef __cplusplus
extern "C" {
#endif
#include "core/federated/federate.h"
#include "core/federated/net_common.h"
#include "core/federated/net_util.h"
#include "core/federated/clock-sync.h"
#include "core/threaded/reactor_threaded.h"
#include "core/utils/util.h"
extern federate_instance_t _fed;
#ifdef __cplusplus
}
#endif
#endif
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    int value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} __pin1_port0_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    int value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} __pin1_port_t;
typedef struct {
    struct self_base_t base;
    
    
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    __pin1_port0_t* _lf_port0;
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    // width of -2 indicates that it is not a multiport.
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    int _lf_port0_width;
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    // Default input (in case it does not get connected)
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    __pin1_port0_t _lf_default__port0;
    #line 54 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    __pin1_port_t _lf_port;
    #line 54 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    int _lf_port_width;
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    trigger_t _lf__port0;
    #ifdef FEDERATED
    
    #endif // FEDERATED
} __pin1_self_t;
__pin1_self_t* new___pin1();
#endif // __PIN1_H
