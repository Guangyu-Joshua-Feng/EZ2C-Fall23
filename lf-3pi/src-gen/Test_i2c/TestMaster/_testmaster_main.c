#include "include/api/api.h"
#include "include/TestMaster/TestMaster.h"
#include "_testmaster_main.h"
// *********** From the preamble, verbatim:
#line 39 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
static bool addr_taken[MAX_SLAVES];

static inline addr_at_index(int i) {
  return i + I2C_DEFAULT_SLAVE_ADDR + 1;
}

static void setup_master() {
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

  for (int i = 0; i < MAX_SLAVES; ++i) {
    addr_taken[i] = false;
  }
}

// Dynamic address allocation helper methods.
static bool discover();
static void assign(pico_unique_board_id_t id);
static uint8_t get_next_addr();
static void echo(uint8_t slave_addr);

static bool discover() {
  uint8_t command = COMMAND_DISCOVER;
  int bytes_sent = i2c_write_blocking(i2c0, I2C_DEFAULT_SLAVE_ADDR, &command, 1, false);
  printf("Discover bytes sent: %d\n", bytes_sent);
  if (bytes_sent == 1) {
    // at least one slave device got the command
    pico_unique_board_id_t id;
    int bytes_recvd = i2c_read_blocking(i2c0, I2C_DEFAULT_SLAVE_ADDR, &id, sizeof(id), false);
    printf("Discover unique id size returned %d\n", bytes_recvd);
    assign(id);
    return true;
  } else {
    return false;
  }
}

static void assign(pico_unique_board_id_t id) {
  printf("assigning address for id %llx\n", *(uint64_t *)&id);
  uint8_t addr = get_next_addr();
  if (addr == (uint8_t)-1) {
    printf("assign: max address reached\n");
    return;
  }
  printf("Assigning %x as the new slave address\n", addr);

  // Format: [address reassignment command | unique identifier | new address]
  uint8_t buf[2 + sizeof(pico_unique_board_id_t)];
  buf[0] = COMMAND_ASSIGN;
  memcpy(buf + 1, &id, sizeof(id));
  buf[1 + sizeof(pico_unique_board_id_t)] = addr;

  int bytes_sent = i2c_write_blocking(i2c0, I2C_DEFAULT_SLAVE_ADDR, buf, sizeof(buf), false);
  printf("Assignment command bytes sent: %d\n", bytes_sent);

  // Echo device at new address to test connectivity.
  echo(addr);
}

static uint8_t get_next_addr() {
  int i = 0;
  while (addr_taken[i] && i < MAX_SLAVES) {
    ++i;
  }
  if (i == MAX_SLAVES) return -1;

  addr_taken[i] = true;
  return addr_at_index(i);
}

static void echo(uint8_t slave_addr) {
  static const char *const msg = "Master Sent!";
  uint8_t buf[32];
  buf[0] = COMMAND_ECHO;
  memcpy(buf, msg, strlen(msg) + 1);
  printf("echoing slave at address %x\n", slave_addr);
  int bytes_sent = i2c_write_blocking(i2c0, slave_addr, msg, 2+strlen(msg), false);
  printf("bytes sent: %d\n", bytes_sent);

  uint8_t recv[32] = {0};
  int bytes_read = i2c_read_blocking(i2c0, slave_addr, recv, 1+strlen(msg), false);
  printf("slave sent back %d bytes: %s\n", bytes_read, recv);
}

// *********** End of preamble.
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/set.h"
void _testmaster_mainreaction_function_0(void* instance_args) {
    _testmaster_main_main_self_t* self = (_testmaster_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 140 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    setup_master();
    gpio_init(0);
    gpio_set_dir(0, GPIO_IN);
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _testmaster_mainreaction_function_1(void* instance_args) {
    _testmaster_main_main_self_t* self = (_testmaster_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _testmaster_main_button_t* button = &self->_lf_button;
    #line 146 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    // Scan button press
    if (gpio_get(0)) {
      lf_schedule(button,0);
    }
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _testmaster_mainreaction_function_2(void* instance_args) {
    _testmaster_main_main_self_t* self = (_testmaster_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    // Expose the action struct as a local variable whose name matches the action name.
    _testmaster_main_button_t* button = &self->_lf_button;
    // Set the fields of the action struct to match the current trigger.
    button->is_present = (bool)self->_lf__button.status;
    button->has_value = ((self->_lf__button.tmplt.token) != NULL && (self->_lf__button.tmplt.token)->value != NULL);
    _lf_replace_template_token((token_template_t*)button, (self->_lf__button.tmplt.token));
    #line 153 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    printf("button pressed\n");
    self->discover_done = false;
    while (!self->discover_done) {
      self->discover_done = !discover();
    }
}
#include "include/api/set_undef.h"
#include "include/api/set.h"
void _testmaster_mainreaction_function_3(void* instance_args) {
    _testmaster_main_main_self_t* self = (_testmaster_main_main_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 161 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    for (int i = 0; i < MAX_SLAVES; ++i) {
      if (addr_taken[i]) echo(addr_at_index(i));
    }
}
#include "include/api/set_undef.h"
_testmaster_main_main_self_t* new__testmaster_main() {
    _testmaster_main_main_self_t* self = (_testmaster_main_main_self_t*)_lf_new_reactor(sizeof(_testmaster_main_main_self_t));
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf_button._base.trigger = &self->_lf__button;
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf_button.parent = (self_base_t*)self;
    #line 139 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_0.number = 0;
    #line 139 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_0.function = _testmaster_mainreaction_function_0;
    #line 139 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_0.self = self;
    #line 139 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    #line 139 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_0.STP_handler = NULL;
    #line 139 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_0.name = "?";
    #line 139 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_0.mode = NULL;
    #line 145 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_1.number = 1;
    #line 145 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_1.function = _testmaster_mainreaction_function_1;
    #line 145 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_1.self = self;
    #line 145 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    #line 145 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_1.STP_handler = NULL;
    #line 145 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_1.name = "?";
    #line 145 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_1.mode = NULL;
    #line 152 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_2.number = 2;
    #line 152 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_2.function = _testmaster_mainreaction_function_2;
    #line 152 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_2.self = self;
    #line 152 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_2.deadline_violation_handler = NULL;
    #line 152 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_2.STP_handler = NULL;
    #line 152 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_2.name = "?";
    #line 152 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_2.mode = NULL;
    #line 160 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_3.number = 3;
    #line 160 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_3.function = _testmaster_mainreaction_function_3;
    #line 160 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_3.self = self;
    #line 160 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_3.deadline_violation_handler = NULL;
    #line 160 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_3.STP_handler = NULL;
    #line 160 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_3.name = "?";
    #line 160 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__reaction_3.mode = NULL;
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button_scan_t.last = NULL;
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button_scan_t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button_scan_t_reactions[0] = &self->_lf__reaction_1;
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button_scan_t.reactions = &self->_lf__button_scan_t_reactions[0];
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button_scan_t.number_of_reactions = 1;
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #ifdef FEDERATED
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button_scan_t.physical_time_of_arrival = NEVER;
    #line 135 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #endif // FEDERATED
    self->_lf__button_scan_t.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__button_scan_t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__echo_t.last = NULL;
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__echo_t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__echo_t_reactions[0] = &self->_lf__reaction_3;
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__echo_t.reactions = &self->_lf__echo_t_reactions[0];
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__echo_t.number_of_reactions = 1;
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #ifdef FEDERATED
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__echo_t.physical_time_of_arrival = NEVER;
    #line 136 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #endif // FEDERATED
    self->_lf__echo_t.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__echo_t.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__startup.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__startup_reactions[0] = &self->_lf__reaction_0;
    self->_lf__startup.last = NULL;
    self->_lf__startup.reactions = &self->_lf__startup_reactions[0];
    self->_lf__startup.number_of_reactions = 1;
    self->_lf__startup.is_timer = false;
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button.last = NULL;
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #ifdef FEDERATED_DECENTRALIZED
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #endif // FEDERATED_DECENTRALIZED
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button_reactions[0] = &self->_lf__reaction_2;
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button.reactions = &self->_lf__button_reactions[0];
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button.number_of_reactions = 1;
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #ifdef FEDERATED
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    self->_lf__button.physical_time_of_arrival = NEVER;
    #line 137 "/home/foobar/EZ2C-Fall23/lf-3pi/src/Test_i2c/TestMaster.lf"
    #endif // FEDERATED
    self->_lf__button.is_physical = false;
    
    self->_lf__button.tmplt.type.element_size = 0;
    self->_lf_button.type.element_size = 0;
    return self;
}
