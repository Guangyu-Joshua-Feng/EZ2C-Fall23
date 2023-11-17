#include "include/api/api.h"
#include "include/CircularSlave/CircularSlave.h"
#include "_circularslave_main.h"
// *********** From the preamble, verbatim:
#line 32 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
static struct {
  uint8_t mem[256];
  uint8_t mem_address;
} context;

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event);

static void process_command() {
  pico_unique_board_id_t my_id;
  switch (context.mem[0]) {
    case COMMAND_DISCOVER:
      // get id ready for master to read
      pico_get_unique_board_id(context.mem);
      break;

    case COMMAND_ASSIGN:
      // check if this command is for me
      pico_get_unique_board_id(&my_id);
      if (memcmp(&my_id, context.mem + 1, sizeof(my_id)) != 0) {
        // if id doesn't match, terminate
        return;
      }

      // reassign my address
      uint8_t addr = context.mem[1 + sizeof(my_id)];
      i2c_slave_init(i2c0, addr, &i2c_slave_handler);
      break;

    case COMMAND_ECHO:
      // move data to the beginning of mem for master to read
      memmove(context.mem, context.mem + 1, strlen(context.mem + 1));
      break;

    default:
      break;
  }
}

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
  static bool recvd = false;
  switch (event) {
  case I2C_SLAVE_RECEIVE: // master has written some data
      // save into memory
      recvd = true;
      context.mem[context.mem_address] = i2c_read_byte_raw(i2c);
      context.mem_address++;
      break;

  case I2C_SLAVE_REQUEST: // master is requesting data
      // load from memory
      i2c_write_byte_raw(i2c, context.mem[context.mem_address]);
      context.mem_address++;
      break;

  case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
      context.mem_address = 0;
      if (recvd) {
        recvd = false;
        process_command();
      }
      break;

  default:
      break;
  }
}

static void setup_slave() {
  gpio_init(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_init(PICO_DEFAULT_I2C_SCL_PIN);
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
  if (INTERNAL_PULL_UP) {
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
  } else {
    gpio_disable_pulls(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_disable_pulls(PICO_DEFAULT_I2C_SCL_PIN);
  }
  i2c_init(i2c0, 100);
  i2c_slave_init(i2c0, I2C_DEFAULT_SLAVE_ADDR, &i2c_slave_handler);
}

// *********** End of preamble.
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _circularslave_mainreaction_function_0(void* instance_args) {
    _circularslave_main_main_self_t* self = (_circularslave_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 117 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    setup_slave();
}
#include "include/api/set_undef.h"
_circularslave_main_main_self_t* new__circularslave_main() {
    _circularslave_main_main_self_t* self = (_circularslave_main_main_self_t*)_lf_new_reactor(sizeof(_circularslave_main_main_self_t));
    #line 116 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    self->_lf__reaction_0.number = 0;
    #line 116 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    self->_lf__reaction_0.function = _circularslave_mainreaction_function_0;
    #line 116 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    self->_lf__reaction_0.self = self;
    #line 116 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 116 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 116 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    self->_lf__reaction_0.name = "?";
    #line 116 "/home/ee149/EZ2C-Fall23/lf-3pi/src/circular/CircularSlave.lf"
    self->_lf__reaction_0.mode = NULL;
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
