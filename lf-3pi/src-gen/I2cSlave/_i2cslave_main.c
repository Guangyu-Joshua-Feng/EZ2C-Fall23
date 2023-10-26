#include "include/api/api.h"
#include "include/I2cSlave/I2cSlave.h"
#include "_i2cslave_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _i2cslave_mainreaction_function_0(void* instance_args) {
    _i2cslave_main_main_self_t* self = (_i2cslave_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 23 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    // LED Initialization
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    // I2C initialization
    i2c_init(i2c_default, 400 * 1000);
    i2c_set_slave_mode(i2c_default, true, ADDR);
    
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _i2cslave_mainreaction_function_1(void* instance_args) {
    _i2cslave_main_main_self_t* self = (_i2cslave_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 38 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    char c;
    i2c_read_raw_blocking(i2c_default, &c, 1);
    if (c == 'h') {
      self->led_on = !self->led_on;
      gpio_put(PICO_DEFAULT_LED_PIN, !self->led_on);
    }
}
#include "include/api/set_undef.h"
_i2cslave_main_main_self_t* new__i2cslave_main() {
    _i2cslave_main_main_self_t* self = (_i2cslave_main_main_self_t*)_lf_new_reactor(sizeof(_i2cslave_main_main_self_t));
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.number = 0;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.function = _i2cslave_mainreaction_function_0;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.self = self;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.name = "?";
    #line 22 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.number = 1;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.function = _i2cslave_mainreaction_function_1;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.self = self;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.STP_handler = NULL;
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.name = "?";
    #line 37 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.mode = NULL;
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.last = NULL;
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t_reactions[0] = &self->_lf__reaction_1;
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.reactions = &self->_lf__t_reactions[0];
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.number_of_reactions = 1;
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    #ifdef FEDERATED
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.physical_time_of_arrival = NEVER;
    #line 19 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
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
