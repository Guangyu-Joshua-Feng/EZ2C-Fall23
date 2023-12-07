#include "common.h"

#include <pico/stdlib.h>

const uint US_PER_MS = 1000U;
const uint8_t COMMAND_DISCOVER = 0;
const uint8_t COMMAND_ASSIGN = 1;
const uint8_t COMMAND_ECHO = 2;
const uint8_t I2C_DEFAULT_SLAVE_ADDR = 0x55;
