#pragma once

#include <hardware/pio.h>
#include <pico/stdlib.h>

void rise_time_init(uint lo_pin, uint hi_pin, uint rise_count_limit,
                    void (*callback)(void), PIO *pio_hw, uint *sm);

float get_avg_cycles(PIO pio_hw, uint sm);

void rise_time_continue(PIO pio_hw, uint sm);

void rise_time_reset_rise_count_limit(PIO pio_hw, uint sm,
                                      uint rise_count_limit);
