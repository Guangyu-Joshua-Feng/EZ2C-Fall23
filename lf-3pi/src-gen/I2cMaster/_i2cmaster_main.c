#include "include/api/api.h"
#include "include/I2cMaster/I2cMaster.h"
#include "_i2cmaster_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _i2cmaster_mainreaction_function_0(void* instance_args) {
    _i2cmaster_main_main_self_t* self = (_i2cmaster_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 28 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _i2cmaster_mainreaction_function_1(void* instance_args) {
    _i2cmaster_main_main_self_t* self = (_i2cmaster_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    char c = 'h';
    i2c_write_blocking(i2c_default, ADDR, &c, 1, false);
}
#include "include/api/set_undef.h"
_i2cmaster_main_main_self_t* new__i2cmaster_main() {
    _i2cmaster_main_main_self_t* self = (_i2cmaster_main_main_self_t*)_lf_new_reactor(sizeof(_i2cmaster_main_main_self_t));
    #line 27 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_0.number = 0;
    #line 27 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_0.function = _i2cmaster_mainreaction_function_0;
    #line 27 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_0.self = self;
    #line 27 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 27 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 27 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_0.name = "?";
    #line 27 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_1.number = 1;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_1.function = _i2cmaster_mainreaction_function_1;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_1.self = self;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_1.STP_handler = NULL;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_1.name = "?";
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__reaction_1.mode = NULL;
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__t.last = NULL;
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__t_reactions[0] = &self->_lf__reaction_1;
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__t.reactions = &self->_lf__t_reactions[0];
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__t.number_of_reactions = 1;
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    #ifdef FEDERATED
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
    self->_lf__t.physical_time_of_arrival = NEVER;
    #line 24 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cMaster.lf"
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
