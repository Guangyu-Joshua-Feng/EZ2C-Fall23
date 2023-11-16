#ifndef _DOUNT_H
#define _DOUNT_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_174238859_H
#define TOP_LEVEL_PREAMBLE_174238859_H
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
} _dount_out_t;
typedef struct {
    struct self_base_t base;
    
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    int c;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    _dount_out_t _lf_out;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    int _lf_out_width;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    reaction_t _lf__reaction_0;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    trigger_t _lf__t;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    reaction_t* _lf__t_reactions[1];
} _dount_self_t;
_dount_self_t* new__dount();
#endif // _DOUNT_H
