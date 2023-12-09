#include "rise_time.h"

#include <hardware/clocks.h>
#include <hardware/gpio.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>
#include <rise_time.pio.h>

#include "pio_utils.h"

// Number of clock cycles per PIO counter increment. Adjust this according
// to the assembly program in rise_time.pio.
#define PIO_CYCLES_PER_COUNTER_INCERMENT 5
#define OUTPUT_SIGNAL 1

static uint offsets[2];

static inline int pio_hw_number(PIO pio_hw);

void rise_time_init(uint lo_pin, uint hi_pin, void (*callback)(void),
                    PIO *pio_hw, uint *sm) {
    uint offset = 0;
    if (!pio_lib_utils_init_pio(&rise_time_program, pio_hw, sm, &offset)) {
        panic("failed to setup pio");
    }
    rise_time_program_init(*pio_hw, *sm, offset, lo_pin, hi_pin);
    int pio_number = pio_hw_number(pio_hw);
    offsets[pio_number] = offset;

    // Set up IRQ.
    int8_t nvic_pio_irq = pio_lib_utils_find_available_nvic_irq(*pio_hw);
    if (nvic_pio_irq < 0) {
        panic("failed to find available nvic irq for pio");
    }
    irq_set_exclusive_handler(nvic_pio_irq, callback);
    irq_set_enabled(nvic_pio_irq, true);
    uint index = pio_lib_utils_get_nvic_pio_irq_index(*pio_hw, nvic_pio_irq);
    pio_set_irqn_source_enabled(*pio_hw, index, pis_interrupt0 + *sm, true);
    pio_set_irqn_source_enabled(*pio_hw, index, pis_interrupt1 + *sm, true);
    pio_set_irqn_source_enabled(*pio_hw, index, pis_interrupt2 + *sm, true);
}

float rise_time_get_avg_cycles(PIO pio_hw, uint sm) {
    uint32_t count = rise_time_program_recv(pio_hw, sm);
    uint32_t rises = rise_time_program_recv(pio_hw, sm);
    if (rises == 0) return 0.0f;
    return (float)PIO_CYCLES_PER_COUNTER_INCERMENT * count / rises;
}

void rise_time_signal_output(PIO pio_hw, uint sm) {
    // Send output signal to TX FIFO.
    pio_sm_put(pio_hw, sm, OUTPUT_SIGNAL);
}

void rise_time_reset(PIO pio_hw, uint sm) {
    int pio_number = pio_hw_number(pio_hw);
    uint offset = offsets[pio_number];

    // Encode a "jump to program start" instruction...
    uint instr_jmp_init = pio_encode_jmp(offset);

    // And send it to the target state machine to execute.
    pio_sm_exec(pio_hw, sm, instr_jmp_init);
    pio_sm_restart(pio_hw, sm);
}

static inline int pio_hw_number(PIO pio_hw) {
    // 1 if true, 0 otherwise.
    return pio_hw == pio1;
}
