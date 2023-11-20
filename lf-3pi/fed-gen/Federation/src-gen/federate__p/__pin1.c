#include "include/api/api.h"
#include "include/federate__p/_pin1.h"
#include "__pin1.h"
// ***** Start of method declarations.
// ***** End of method declarations.
__pin1_self_t* new___pin1() {
    __pin1_self_t* self = (__pin1_self_t*)_lf_new_reactor(sizeof(__pin1_self_t));
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    // Set input by default to an always absent default input.
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf_port0 = &self->_lf_default__port0;
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    // Set the default source reactor pointer
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf_default__port0._base.source_reactor = (self_base_t*)self;
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__port0.last = NULL;
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__port0.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 52 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__port0.tmplt.type.element_size = sizeof(int);
    return self;
}
