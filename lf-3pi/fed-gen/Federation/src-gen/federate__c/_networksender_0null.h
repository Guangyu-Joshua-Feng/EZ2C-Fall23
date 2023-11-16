#ifndef _NETWORKSENDER_0NULL_H
#define _NETWORKSENDER_0NULL_H
#include "include/core/reactor.h"
#ifndef TOP_LEVEL_PREAMBLE_42668921_H
#define TOP_LEVEL_PREAMBLE_42668921_H
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
} _networksender_0null_msg_t;
typedef struct {
    struct self_base_t base;
    
    
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    _networksender_0null_msg_t* _lf_msg;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    // width of -2 indicates that it is not a multiport.
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    int _lf_msg_width;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    // Default input (in case it does not get connected)
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    _networksender_0null_msg_t _lf_default__msg;
    #line 47 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    reaction_t _lf__reaction_0;
    #line 56 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    reaction_t _lf__reaction_1;
    #line 65 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    reaction_t _lf__reaction_2;
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    trigger_t _lf__msg;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c.lf"
    reaction_t* _lf__msg_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _networksender_0null_self_t;
_networksender_0null_self_t* new__networksender_0null();
#endif // _NETWORKSENDER_0NULL_H
