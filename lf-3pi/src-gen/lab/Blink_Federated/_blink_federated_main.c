#include "include/api/api.h"
#include "include/Blink_Federated/Blink_Federated.h"
#include "_blink_federated_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _blink_federated_mainreaction_function_0(void* instance_args) {
    _blink_federated_main_main_self_t* self = (_blink_federated_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 26 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    gpio_init(16);
    gpio_set_dir(16, GPIO_OUT);
    gpio_init(0);
    gpio_set_dir(0, GPIO_OUT);
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _blink_federated_mainreaction_function_1(void* instance_args) {
    _blink_federated_main_main_self_t* self = (_blink_federated_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 33 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->led_on = !self->led_on;
    gpio_put(16, !self->led_on);
    gpio_put(0, !self->led_on);
}
#include "include/api/set_undef.h"
_blink_federated_main_main_self_t* new__blink_federated_main() {
    _blink_federated_main_main_self_t* self = (_blink_federated_main_main_self_t*)_lf_new_reactor(sizeof(_blink_federated_main_main_self_t));
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_0.number = 0;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_0.function = _blink_federated_mainreaction_function_0;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_0.self = self;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_0.name = "?";
    #line 25 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 32 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_1.number = 1;
    #line 32 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_1.function = _blink_federated_mainreaction_function_1;
    #line 32 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_1.self = self;
    #line 32 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    #line 32 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_1.STP_handler = NULL;
    #line 32 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_1.name = "?";
    #line 32 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__reaction_1.mode = NULL;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__t.last = NULL;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__t_reactions[0] = &self->_lf__reaction_1;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__t.reactions = &self->_lf__t_reactions[0];
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__t.number_of_reactions = 1;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    #ifdef FEDERATED
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    self->_lf__t.physical_time_of_arrival = NEVER;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/lab/Blink_Federated.lf"
    #endif // FEDERATED
    self->_lf__t.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__startup.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__startup_reactions[0] = &self->_lf__reaction_0;
    self->_lf__startup.last = NULL;
    self->_lf__startup.reactions = &self->_lf__startup_reactions[0];
    self->_lf__startup.number_of_reactions = 1;
    self->_lf__startup.is_timer = false;
    return self;
}
