#include "include/api/api.h"
#include "include/federate__d/NetworkSender_00.h"
#include "_networksender_0null.h"
#if defined SENDERINDEXPARAMETER
#undef SENDERINDEXPARAMETER
#endif // SENDERINDEXPARAMETER
#define SENDERINDEXPARAMETER 0
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _networksender_0nullreaction_function_0(void* instance_args) {
    _networksender_0null_self_t* self = (_networksender_0null_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 48 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    extern reaction_t* port_absent_reaction[];
    void enqueue_port_absent_reactions(environment_t*);
    LF_PRINT_DEBUG("Adding network port absent reaction to table.");
    port_absent_reaction[SENDERINDEXPARAMETER] = &self->_lf__reaction_2;
    LF_PRINT_DEBUG("Added network output control reaction to table. Enqueueing it...");
    enqueue_port_absent_reactions(self->base.environment);
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _networksender_0nullreaction_function_1(void* instance_args) {
    _networksender_0null_self_t* self = (_networksender_0null_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _networksender_0null_msg_t* msg = self->_lf_msg;
    int msg_width = self->_lf_msg_width; SUPPRESS_UNUSED_WARNING(msg_width);
    #line 57 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    // Sending from msg in federate federate__d to p.in2 in federate federate__p
    if (!msg->is_present) {
    return;
    }
    size_t _lf_message_length = sizeof(int);
    send_timed_message(self->base.environment, NEVER, MSG_TYPE_TAGGED_MESSAGE, 1, 2, "federate 2 via the RTI", _lf_message_length, (unsigned char*)&msg->value);
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _networksender_0nullreaction_function_2(void* instance_args) {
    _networksender_0null_self_t* self = (_networksender_0null_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _networksender_0null_msg_t* msg = self->_lf_msg;
    int msg_width = self->_lf_msg_width; SUPPRESS_UNUSED_WARNING(msg_width);
    #line 66 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    // If the output port has not been lf_set for the current logical time,
    // send an ABSENT message to the receiving federate
    LF_PRINT_LOG("Executing port absent reaction for port %d to federate %d at time %lld.",
              1, 2, (long long) lf_time_logical_elapsed());
    if (msg == NULL || !msg->is_present) {
    LF_PRINT_LOG("The output port is NULL or it is not present.");
        send_port_absent_to_federate(self->base.environment, NEVER, 1, 2);
    }
}
#include "include/api/set_undef.h"
_networksender_0null_self_t* new__networksender_0null() {
    _networksender_0null_self_t* self = (_networksender_0null_self_t*)_lf_new_reactor(sizeof(_networksender_0null_self_t));
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    // Set input by default to an always absent default input.
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf_msg = &self->_lf_default__msg;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    // Set the default source reactor pointer
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf_default__msg._base.source_reactor = (self_base_t*)self;
    #line 47 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_0.number = 0;
    #line 47 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_0.function = _networksender_0nullreaction_function_0;
    #line 47 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_0.self = self;
    #line 47 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 47 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 47 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_0.name = "?";
    #line 47 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 56 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_1.number = 1;
    #line 56 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_1.function = _networksender_0nullreaction_function_1;
    #line 56 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_1.self = self;
    #line 56 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    #line 56 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_1.STP_handler = NULL;
    #line 56 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_1.name = "?";
    #line 56 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_1.mode = NULL;
    #line 65 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_2.number = 2;
    #line 65 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_2.function = _networksender_0nullreaction_function_2;
    #line 65 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_2.self = self;
    #line 65 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_2.deadline_violation_handler = NULL;
    #line 65 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_2.STP_handler = NULL;
    #line 65 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_2.name = "?";
    #line 65 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__reaction_2.mode = NULL;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__startup.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__startup_reactions[0] = &self->_lf__reaction_0;
    self->_lf__startup.last = NULL;
    self->_lf__startup.reactions = &self->_lf__startup_reactions[0];
    self->_lf__startup.number_of_reactions = 1;
    self->_lf__startup.is_timer = false;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__msg.last = NULL;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__msg.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__msg_reactions[0] = &self->_lf__reaction_1;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__msg.reactions = &self->_lf__msg_reactions[0];
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__msg.number_of_reactions = 1;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    #ifdef FEDERATED
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    self->_lf__msg.physical_time_of_arrival = NEVER;
    #line 45 "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf"
    #endif // FEDERATED
    self->_lf__msg.tmplt.type.element_size = sizeof(int);
    return self;
}
