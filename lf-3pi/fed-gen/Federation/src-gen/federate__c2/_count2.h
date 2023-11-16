#ifndef _COUNT2_H
#define _COUNT2_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_329440770_H
#define TOP_LEVEL_PREAMBLE_329440770_H
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
} _count2_out_t;
typedef struct {
    struct self_base_t base;
    
    #line 35 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    int c;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    _count2_out_t _lf_out;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    int _lf_out_width;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    reaction_t _lf__reaction_0;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    trigger_t _lf__t;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    reaction_t* _lf__t_reactions[1];
} _count2_self_t;
_count2_self_t* new__count2();
#endif // _COUNT2_H
