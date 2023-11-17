#include "include/api/api.h"
#include "include/core/platform.h"
#include "include/federate__d/Dount.h"
#include "_dount.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _dountreaction_function_0(void* instance_args) {
    _dount_self_t* self = (_dount_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _dount_out_t* out = &self->_lf_out;
    #line 40 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    lf_set(out, self->c++);
#line 14 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__d/_dount.c"
}
#include "include/api/set_undef.h"
_dount_self_t* new__dount() {
    _dount_self_t* self = (_dount_self_t*)_lf_new_reactor(sizeof(_dount_self_t));
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _dountreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__t.last = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__t_reactions[0] = &self->_lf__reaction_0;
    self->_lf__t.reactions = &self->_lf__t_reactions[0];
    self->_lf__t.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__t.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__t.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    return self;
}
