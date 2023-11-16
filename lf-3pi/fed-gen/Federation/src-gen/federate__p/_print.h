#ifndef _PRINT_H
#define _PRINT_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_1811954558_H
#define TOP_LEVEL_PREAMBLE_1811954558_H
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
} _print_in1_t;
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
} _print_in2_t;
typedef struct {
    struct self_base_t base;
    
    
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    _print_in1_t* _lf_in1;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    // width of -2 indicates that it is not a multiport.
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    int _lf_in1_width;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    // Default input (in case it does not get connected)
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    _print_in1_t _lf_default__in1;
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    _print_in2_t* _lf_in2;
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    // width of -2 indicates that it is not a multiport.
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    int _lf_in2_width;
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    // Default input (in case it does not get connected)
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    _print_in2_t _lf_default__in2;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    reaction_t _lf__reaction_0;
    #line 44 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    reaction_t _lf__reaction_1;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    trigger_t _lf__in1;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    reaction_t* _lf__in1_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    trigger_t _lf__in2;
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    reaction_t* _lf__in2_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _print_self_t;
_print_self_t* new__print();
#endif // _PRINT_H
