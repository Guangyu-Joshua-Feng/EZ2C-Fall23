#include "include/api/api.h"
#include "include/federate__p/Print.h"
#include "_print.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _printreaction_function_0(void* instance_args) {
    _print_self_t* self = (_print_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _print_in_t* in = self->_lf_in;
    int in_width = self->_lf_in_width; SUPPRESS_UNUSED_WARNING(in_width);
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    lf_print("Received: %d at (%lld, %d)", in->value,
        lf_time_logical_elapsed(), lf_tag().microstep
    );
}
#include "include/api/set_undef.h"
_print_self_t* new__print() {
    _print_self_t* self = (_print_self_t*)_lf_new_reactor(sizeof(_print_self_t));
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    // Set input by default to an always absent default input.
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf_in = &self->_lf_default__in;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    // Set the default source reactor pointer
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf_default__in._base.source_reactor = (self_base_t*)self;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__reaction_0.number = 0;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__reaction_0.function = _printreaction_function_0;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__reaction_0.self = self;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__reaction_0.name = "?";
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__in.last = NULL;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__in.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__in_reactions[0] = &self->_lf__reaction_0;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__in.reactions = &self->_lf__in_reactions[0];
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__in.number_of_reactions = 1;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    #ifdef FEDERATED
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    self->_lf__in.physical_time_of_arrival = NEVER;
    #line 34 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__p.lf"
    #endif // FEDERATED
    self->_lf__in.tmplt.type.element_size = sizeof(int);
    return self;
}
