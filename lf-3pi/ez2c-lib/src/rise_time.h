#pragma once

#include <hardware/pio.h>
#include <pico/stdlib.h>

void rise_time_init(uint lo_pin, uint hi_pin, void (*callback)(void),
                    PIO *pio_hw, uint *sm);

float rise_time_get_avg_cycles(PIO pio_hw, uint sm);

void rise_time_signal_output(PIO pio_hw, uint sm);

void rise_time_reset(PIO pio_hw, uint sm);
