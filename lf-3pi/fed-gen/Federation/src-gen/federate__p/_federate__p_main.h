#ifndef _FEDERATE__P_MAIN_H
#define _FEDERATE__P_MAIN_H
#include "include/core/reactor.h"
#include "_print.h"
#include "_networkreceiver_0.h"
#include "__pin2.h"
#include "__pin1.h"
#include "_networkreceiver_1.h"
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
    struct self_base_t base;
#line 28 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/_federate__p_main.h"
#line 29 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/_federate__p_main.h"
} _federate__p_main_main_self_t;
_federate__p_main_main_self_t* new__federate__p_main();
#endif // _FEDERATE__P_MAIN_H
