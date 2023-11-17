#include "include/api/api.h"
#include "include/core/platform.h"
#include "include/federate__p/NetworkReceiver_1.h"
#include "_networkreceiver_1.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _networkreceiver_1reaction_function_0(void* instance_args) {
    _networkreceiver_1_self_t* self = (_networkreceiver_1_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 87 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    self->_lf__reaction_1.is_an_input_reaction = true;
#line 14 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/_networkreceiver_1.c"
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _networkreceiver_1reaction_function_1(void* instance_args) {
    _networkreceiver_1_self_t* self = (_networkreceiver_1_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    lf_critical_section_enter(self->base.environment);
    // Expose the action struct as a local variable whose name matches the action name.
    _networkreceiver_1_networkMessage_t* networkMessage = &self->_lf_networkMessage;
    // Set the fields of the action struct to match the current trigger.
    networkMessage->is_present = (bool)self->_lf__networkMessage.status;
    networkMessage->has_value = ((self->_lf__networkMessage.tmplt.token) != NULL && (self->_lf__networkMessage.tmplt.token)->value != NULL);
    _lf_replace_template_token((token_template_t*)networkMessage, (self->_lf__networkMessage.tmplt.token));
    if (networkMessage->has_value) {
        networkMessage->value = *(int*)(self->_lf__networkMessage.tmplt.token)->value;
    }
    lf_critical_section_exit(self->base.environment);
    _networkreceiver_1_msg_t* msg = &self->_lf_msg;
    #line 91 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__p.lf"
    msg->physical_time_of_arrival = self->_lf__networkMessage.physical_time_of_arrival;
    lf_set(msg, networkMessage->value);
#line 35 "/home/ee149/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__p/_networkreceiver_1.c"
}
#include "include/api/set_undef.h"
_networkreceiver_1_self_t* new__networkreceiver_1() {
    _networkreceiver_1_self_t* self = (_networkreceiver_1_self_t*)_lf_new_reactor(sizeof(_networkreceiver_1_self_t));
    self->_lf_networkMessage._base.trigger = &self->_lf__networkMessage;
    self->_lf_networkMessage.parent = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _networkreceiver_1reaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _networkreceiver_1reaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__startup.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__startup_reactions[0] = &self->_lf__reaction_0;
    self->_lf__startup.last = NULL;
    self->_lf__startup.reactions = &self->_lf__startup_reactions[0];
    self->_lf__startup.number_of_reactions = 1;
    self->_lf__startup.is_timer = false;
    self->_lf__networkMessage.last = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__networkMessage.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__networkMessage_reactions[0] = &self->_lf__reaction_1;
    self->_lf__networkMessage.reactions = &self->_lf__networkMessage_reactions[0];
    self->_lf__networkMessage.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__networkMessage.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__networkMessage.is_physical = false;
    
    self->_lf__networkMessage.tmplt.type.element_size = sizeof(int);
    self->_lf_networkMessage.type.element_size = sizeof(int);
    return self;
}
