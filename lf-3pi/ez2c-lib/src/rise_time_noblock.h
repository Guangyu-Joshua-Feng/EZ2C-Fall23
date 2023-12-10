#pragma once

#include <hardware/pio.h>
#include <pico/stdlib.h>

void rise_time_noblock_init(uint lo_pin, uint hi_pin, void (*callback)(void),
                            PIO *pio_hw, uint *sm);

uint32_t rise_time_noblock_get_cycles(PIO pio_hw, uint sm);
