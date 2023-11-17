#ifndef _NETWORKRECEIVER_0_H
#define _NETWORKRECEIVER_0_H
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
} _networkreceiver_0_msg_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_action_internal_t _base;
    self_base_t* parent;
    bool has_value;
    int value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _networkreceiver_0_networkMessage_t;
typedef struct {
    struct self_base_t base;
#line 53 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/_networkreceiver_0.h"
#line 54 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/_networkreceiver_0.h"
    _networkreceiver_0_networkMessage_t _lf_networkMessage;
    _networkreceiver_0_msg_t _lf_msg;
    int _lf_msg_width;
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    trigger_t _lf__startup;
    reaction_t* _lf__startup_reactions[1];
    trigger_t _lf__networkMessage;
    reaction_t* _lf__networkMessage_reactions[1];
} _networkreceiver_0_self_t;
_networkreceiver_0_self_t* new__networkreceiver_0();
#endif // _NETWORKRECEIVER_0_H
