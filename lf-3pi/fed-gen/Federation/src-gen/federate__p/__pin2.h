#ifndef __PIN2_H
#define __PIN2_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_1512167587_H
#define TOP_LEVEL_PREAMBLE_1512167587_H
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
} __pin2_port0_t;
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
} __pin2_port_t;
typedef struct {
    struct self_base_t base;
#line 51 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/__pin2.h"
#line 52 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/__pin2.h"
    __pin2_port0_t* _lf_port0;
    // width of -2 indicates that it is not a multiport.
    int _lf_port0_width;
    // Default input (in case it does not get connected)
    __pin2_port0_t _lf_default__port0;
    // Array of output ports.
    __pin2_port_t* _lf_port;
    int _lf_port_width;
    // An array of pointers to the individual ports. Useful
    // for the lf_set macros to work out-of-the-box for
    // multiports in the body of reactions because their 
    // value can be accessed via a -> operator (e.g.,foo[i]->value).
    // So we have to handle multiports specially here a construct that
    // array of pointers.
    __pin2_port_t** _lf_port_pointers;
    trigger_t _lf__port0;
    #ifdef FEDERATED
    
    #endif // FEDERATED
} __pin2_self_t;
__pin2_self_t* new___pin2();
#endif // __PIN2_H
