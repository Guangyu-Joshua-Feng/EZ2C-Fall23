#ifndef _FEDERATE__D_MAIN_H
#define _FEDERATE__D_MAIN_H
#include "include/core/reactor.h"
#include "_dount.h"
#include "_networksender_0null.h"
#ifndef TOP_LEVEL_PREAMBLE_748482365_H
#define TOP_LEVEL_PREAMBLE_748482365_H
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
#line 25 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__d/_federate__d_main.h"
#line 26 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__d/_federate__d_main.h"
} _federate__d_main_main_self_t;
_federate__d_main_main_self_t* new__federate__d_main();
#endif // _FEDERATE__D_MAIN_H
