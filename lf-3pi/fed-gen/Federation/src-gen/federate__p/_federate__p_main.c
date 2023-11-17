#include "include/api/api.h"
#include "include/core/platform.h"
#include "include/federate__p/federate__p.h"
#include "_federate__p_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
_federate__p_main_main_self_t* new__federate__p_main() {
    _federate__p_main_main_self_t* self = (_federate__p_main_main_self_t*)_lf_new_reactor(sizeof(_federate__p_main_main_self_t));

    return self;
}
