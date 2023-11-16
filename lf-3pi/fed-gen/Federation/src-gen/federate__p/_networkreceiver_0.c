#include "include/api/api.h"
#include "include/federate__p/NetworkReceiver_0.h"
#include "_networkreceiver_0.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _networkreceiver_0reaction_function_0(void* instance_args) {
    _networkreceiver_0_self_t* self = (_networkreceiver_0_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 72 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.is_an_input_reaction = true;
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _networkreceiver_0reaction_function_1(void* instance_args) {
    _networkreceiver_0_self_t* self = (_networkreceiver_0_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    // Expose the action struct as a local variable whose name matches the action name.
    _networkreceiver_0_networkMessage_t* networkMessage = &self->_lf_networkMessage;
    // Set the fields of the action struct to match the current trigger.
    networkMessage->is_present = (bool)self->_lf__networkMessage.status;
    networkMessage->has_value = ((self->_lf__networkMessage.tmplt.token) != NULL && (self->_lf__networkMessage.tmplt.token)->value != NULL);
    _lf_replace_template_token((token_template_t*)networkMessage, (self->_lf__networkMessage.tmplt.token));
    if (networkMessage->has_value) {
        networkMessage->value = *(int*)(self->_lf__networkMessage.tmplt.token)->value;
    }
    _networkreceiver_0_msg_t* msg = &self->_lf_msg;
    #line 74 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    msg->physical_time_of_arrival = self->_lf__networkMessage.physical_time_of_arrival;
    lf_set(msg, networkMessage->value);
}
#include "include/api/set_undef.h"
_networkreceiver_0_self_t* new__networkreceiver_0() {
    _networkreceiver_0_self_t* self = (_networkreceiver_0_self_t*)_lf_new_reactor(sizeof(_networkreceiver_0_self_t));
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf_networkMessage._base.trigger = &self->_lf__networkMessage;
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf_networkMessage.parent = (self_base_t*)self;
    #line 71 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_0.number = 0;
    #line 71 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_0.function = _networkreceiver_0reaction_function_0;
    #line 71 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_0.self = self;
    #line 71 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 71 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 71 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_0.name = "?";
    #line 71 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 73 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.number = 1;
    #line 73 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.function = _networkreceiver_0reaction_function_1;
    #line 73 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.self = self;
    #line 73 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    #line 73 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.STP_handler = NULL;
    #line 73 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.name = "?";
    #line 73 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.mode = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__startup.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__startup_reactions[0] = &self->_lf__reaction_0;
    self->_lf__startup.last = NULL;
    self->_lf__startup.reactions = &self->_lf__startup_reactions[0];
    self->_lf__startup.number_of_reactions = 1;
    self->_lf__startup.is_timer = false;
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__networkMessage.last = NULL;
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__networkMessage.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__networkMessage_reactions[0] = &self->_lf__reaction_1;
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__networkMessage.reactions = &self->_lf__networkMessage_reactions[0];
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__networkMessage.number_of_reactions = 1;
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    #ifdef FEDERATED
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__networkMessage.physical_time_of_arrival = NEVER;
    #line 69 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    #endif // FEDERATED
    self->_lf__networkMessage.is_physical = false;
    
    self->_lf__networkMessage.tmplt.type.element_size = sizeof(int);
    self->_lf_networkMessage.type.element_size = sizeof(int);
    return self;
}
