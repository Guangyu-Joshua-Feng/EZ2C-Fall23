#include "include/api/api.h"
#include "include/core/platform.h"
#include "include/federate__p/_pin2.h"
#include "__pin2.h"
// ***** Start of method declarations.
// ***** End of method declarations.
__pin2_self_t* new___pin2() {
    __pin2_self_t* self = (__pin2_self_t*)_lf_new_reactor(sizeof(__pin2_self_t));
    // Set input by default to an always absent default input.
    self->_lf_port0 = &self->_lf_default__port0;
    // Set the default source reactor pointer
    self->_lf_default__port0._base.source_reactor = (self_base_t*)self;
    self->_lf__port0.last = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__port0.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__port0.tmplt.type.element_size = sizeof(int);
    return self;
}
