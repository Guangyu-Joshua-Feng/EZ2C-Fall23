#include "include/api/api.h"
#include "include/core/platform.h"
#include "include/federate__d/federate__d.h"
#include "_federate__d_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
_federate__d_main_main_self_t* new__federate__d_main() {
    _federate__d_main_main_self_t* self = (_federate__d_main_main_self_t*)_lf_new_reactor(sizeof(_federate__d_main_main_self_t));

    return self;
}
