#include "include/api/api.h"
#include "include/federate__c/Count.h"
#include "_count.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _countreaction_function_0(void* instance_args) {
    _count_self_t* self = (_count_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _count_out_t* out = &self->_lf_out;
    #line 40 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    lf_set(out, self->c++);
}
#include "include/api/set_undef.h"
_count_self_t* new__count() {
    _count_self_t* self = (_count_self_t*)_lf_new_reactor(sizeof(_count_self_t));
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__reaction_0.number = 0;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__reaction_0.function = _countreaction_function_0;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__reaction_0.self = self;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__reaction_0.name = "?";
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__t.last = NULL;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__t_reactions[0] = &self->_lf__reaction_0;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__t.reactions = &self->_lf__t_reactions[0];
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__t.number_of_reactions = 1;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    #ifdef FEDERATED
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    self->_lf__t.physical_time_of_arrival = NEVER;
    #line 36 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/federation/src/federate__c.lf"
    #endif // FEDERATED
    self->_lf__t.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    return self;
}
