#include "include/api/api.h"
#include "include/federate__c2/Count2.h"
#include "_count2.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _count2reaction_function_0(void* instance_args) {
    _count2_self_t* self = (_count2_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _count2_out_t* out = &self->_lf_out;
    #line 40 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    lf_set(out, self->c++);
}
#include "include/api/set_undef.h"
_count2_self_t* new__count2() {
    _count2_self_t* self = (_count2_self_t*)_lf_new_reactor(sizeof(_count2_self_t));
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__reaction_0.number = 0;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__reaction_0.function = _count2reaction_function_0;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__reaction_0.self = self;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__reaction_0.name = "?";
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__t.last = NULL;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__t_reactions[0] = &self->_lf__reaction_0;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__t.reactions = &self->_lf__t_reactions[0];
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__t.number_of_reactions = 1;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    #ifdef FEDERATED
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    self->_lf__t.physical_time_of_arrival = NEVER;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__c2.lf"
    #endif // FEDERATED
    self->_lf__t.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    return self;
}
