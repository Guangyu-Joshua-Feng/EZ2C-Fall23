#pragma once

#include <hardware/pio.h>
#include <pico/stdlib.h>

bool pio_lib_utils_init_pio(const pio_program_t *program, PIO *pio_hw, uint *sm,
                            uint *offset);
int8_t pio_lib_utils_find_available_nvic_irq(const PIO pio_hw);
uint pio_lib_utils_get_nvic_pio_irq_index(const PIO pio_hw,
                                          int8_t nvic_pio_irq);
