#pragma once

#include <pico/stdlib.h>

extern const uint US_PER_MS;

enum Ez2cCommands {
    COMMAND_DISCOVER,
    COMMAND_ASSIGN,
    COMMAND_ECHO,
    COMMAND_GET_INTERRUPT,
    COMMAND_CLEAR_INTERRUPT,
};
extern const uint8_t I2C_DEFAULT_SLAVE_ADDR;
