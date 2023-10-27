#include "include/api/api.h"
#include "include/I2cSlave/I2cSlave.h"
#include "_i2cslave_main.h"
// *********** From the preamble, verbatim:
#line 30 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
  static bool receive;

  static struct
{
    uint8_t mem[256];
    uint8_t mem_address;
    bool mem_address_written;
} context;

  static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {
    case I2C_SLAVE_RECEIVE: // master has written some data
        if (!context.mem_address_written) {
            // writes always start with the memory address
            context.mem_address = i2c_read_byte_raw(i2c);
            context.mem_address_written = true;
        } else {
            // save into memory
            context.mem[context.mem_address] = i2c_read_byte_raw(i2c);
            context.mem_address++;
        }
        receive = true;
        break;
    case I2C_SLAVE_REQUEST: // master is requesting data
        // load from memory
        i2c_write_byte_raw(i2c, context.mem[context.mem_address]);
        context.mem_address++;
        receive = true;
        break;
    case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
        context.mem_address_written = false;
        receive = true;
        break;
    default:
        break;
    }
  }

  static void setup_master() {

    gpio_init(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_init(PICO_DEFAULT_I2C_SCL_PIN);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    i2c_init(i2c0, 100 * 1000);
    // bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
  }
  static void setup_slave() {

    gpio_init(I2C_MASTER_SDA_PIN);
    gpio_init(I2C_MASTER_SCL_PIN);
    gpio_set_function(I2C_MASTER_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_MASTER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_MASTER_SDA_PIN);
    gpio_pull_up(I2C_MASTER_SCL_PIN);

    i2c_init(i2c1, 100 * 1000);
    // i2c_set_slave_mode(i2c1, true, ADDR);
    i2c_slave_init(i2c1,ADDR,&i2c_slave_handler);  
  }

// *********** End of preamble.
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _i2cslave_mainreaction_function_0(void* instance_args) {
    _i2cslave_main_main_self_t* self = (_i2cslave_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 102 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    // LED Initialization
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    // I2C initialization
    setup_master();
    setup_slave();
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _i2cslave_mainreaction_function_1(void* instance_args) {
    _i2cslave_main_main_self_t* self = (_i2cslave_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 114 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    char c = 'a';
    int sent;
    sent = i2c_write_blocking(i2c0, ADDR, &c, 2, false);
    printf("%d",sent);
    if (receive){
      self->led_on = !self->led_on;
      gpio_put(PICO_DEFAULT_LED_PIN, !self->led_on);
    }
}
#include "include/api/set_undef.h"
_i2cslave_main_main_self_t* new__i2cslave_main() {
    _i2cslave_main_main_self_t* self = (_i2cslave_main_main_self_t*)_lf_new_reactor(sizeof(_i2cslave_main_main_self_t));
    #line 101 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.number = 0;
    #line 101 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.function = _i2cslave_mainreaction_function_0;
    #line 101 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.self = self;
    #line 101 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 101 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 101 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.name = "?";
    #line 101 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 113 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.number = 1;
    #line 113 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.function = _i2cslave_mainreaction_function_1;
    #line 113 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.self = self;
    #line 113 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    #line 113 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.STP_handler = NULL;
    #line 113 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.name = "?";
    #line 113 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__reaction_1.mode = NULL;
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.last = NULL;
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t_reactions[0] = &self->_lf__reaction_1;
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.reactions = &self->_lf__t_reactions[0];
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.number_of_reactions = 1;
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    #ifdef FEDERATED
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
    self->_lf__t.physical_time_of_arrival = NEVER;
    #line 98 "/home/foobar/EZ2C-Fall23/lf-3pi/src/I2cSlave.lf"
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
