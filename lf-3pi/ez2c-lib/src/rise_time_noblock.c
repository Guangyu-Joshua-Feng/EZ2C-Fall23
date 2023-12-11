#include "rise_time_noblock.h"

#include <hardware/clocks.h>
#include <hardware/gpio.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>
#include <rise_time_noblock.pio.h>

#include "pio_utils.h"

// Number of clock cycles per PIO counter increment. Adjust this according
// to the assembly program in rise_time_noblock.pio.
#define PIO_CYCLES_PER_COUNTER_INCERMENT 5

static uint offsets[2];

static inline int pio_hw_number(PIO pio_hw);

int rise_time_noblock_init(uint lo_pin, uint hi_pin, void (*callback)(void),
                           PIO *pio_hw, uint *sm) {
    uint offset = 0;
    if (!pio_lib_utils_init_pio(&rise_time_noblock_program, pio_hw, sm,
                                &offset)) {
        return 1;
    }
    rise_time_noblock_program_init(*pio_hw, *sm, offset, lo_pin, hi_pin);
    int pio_number = pio_hw_number(pio_hw);
    offsets[pio_number] = offset;

    // Set up IRQ.
    int8_t nvic_pio_irq = pio_lib_utils_find_available_nvic_irq(*pio_hw);
    if (nvic_pio_irq < 0) return 2;
    irq_set_exclusive_handler(nvic_pio_irq, callback);
    irq_set_enabled(nvic_pio_irq, true);
    uint index = pio_lib_utils_get_nvic_pio_irq_index(*pio_hw, nvic_pio_irq);
    pio_set_irqn_source_enabled(*pio_hw, index, pis_interrupt0 + *sm, true);
    pio_set_irqn_source_enabled(*pio_hw, index, pis_interrupt1 + *sm, true);
    pio_set_irqn_source_enabled(*pio_hw, index, pis_interrupt2 + *sm, true);

    return 0;
}

uint32_t rise_time_noblock_get_cycles(PIO pio_hw, uint sm) {
    uint32_t x = rise_time_noblock_program_recv(pio_hw, sm);
    return (x - 1) * 5;
}

static inline int pio_hw_number(PIO pio_hw) {
    // 1 if true, 0 otherwise.
    return pio_hw == pio1;
}
