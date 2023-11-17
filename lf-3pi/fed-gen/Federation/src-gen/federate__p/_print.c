#include "include/api/api.h"
#include "include/core/platform.h"
#include "include/federate__p/Print.h"
#include "_print.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _printreaction_function_0(void* instance_args) {
    _print_self_t* self = (_print_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _print_in1_t* in1 = self->_lf_in1;
    int in1_width = self->_lf_in1_width; SUPPRESS_UNUSED_WARNING(in1_width);
    #line 39 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    lf_print("Received: %d from Count at (%lld, %d)", in1->value,
        lf_time_logical_elapsed(), lf_tag().microstep
    );
#line 17 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/_print.c"
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _printreaction_function_1(void* instance_args) {
    _print_self_t* self = (_print_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _print_in2_t* in2 = self->_lf_in2;
    int in2_width = self->_lf_in2_width; SUPPRESS_UNUSED_WARNING(in2_width);
    #line 46 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    lf_print("Received: %d from Dount at (%lld, %d)", in2->value,
        lf_time_logical_elapsed(), lf_tag().microstep
    );
#line 29 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/_print.c"
}
#include "include/api/set_undef.h"
_print_self_t* new__print() {
    _print_self_t* self = (_print_self_t*)_lf_new_reactor(sizeof(_print_self_t));
    // Set input by default to an always absent default input.
    self->_lf_in1 = &self->_lf_default__in1;
    // Set the default source reactor pointer
    self->_lf_default__in1._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_in2 = &self->_lf_default__in2;
    // Set the default source reactor pointer
    self->_lf_default__in2._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _printreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _printreaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    self->_lf__in1.last = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__in1.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__in1_reactions[0] = &self->_lf__reaction_0;
    self->_lf__in1.reactions = &self->_lf__in1_reactions[0];
    self->_lf__in1.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__in1.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__in1.tmplt.type.element_size = sizeof(int);
    self->_lf__in2.last = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__in2.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__in2_reactions[0] = &self->_lf__reaction_1;
    self->_lf__in2.reactions = &self->_lf__in2_reactions[0];
    self->_lf__in2.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__in2.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__in2.tmplt.type.element_size = sizeof(int);
    return self;
}
