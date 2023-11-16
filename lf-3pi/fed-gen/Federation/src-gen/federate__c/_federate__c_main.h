#ifndef _FEDERATE__C_MAIN_H
#define _FEDERATE__C_MAIN_H
#include "include/core/reactor.h"
#include "_count.h"
#include "_networksender_0null.h"
#ifndef TOP_LEVEL_PREAMBLE_1238814958_H
#define TOP_LEVEL_PREAMBLE_1238814958_H
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
    struct self_base_t base;
    
    
} _federate__c_main_main_self_t;
_federate__c_main_main_self_t* new__federate__c_main();
#endif // _FEDERATE__C_MAIN_H
