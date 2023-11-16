#ifndef _federate__c1_main_H
#define _federate__c1_main_H
#ifndef TOP_LEVEL_PREAMBLE_1361385939_H
#define TOP_LEVEL_PREAMBLE_1361385939_H
/*Correspondence: Range: [(15, 0), (27, 6)) -> Range: [(0, 0), (12, 6)) (verbatim=true; src=/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c1.lf)*/#ifdef __cplusplus
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
#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/api.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct federate__c1_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    int end[0]; // placeholder; MSVC does not compile empty structs
} federate__c1_self_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    int value;

} count1_out_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    int value;

} networksender_00_msg_t;
#endif
