#include <hardware/clocks.h>
#include <hardware/gpio.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>
#include <pio_lib_utils.h>
#include <rise_time.h>
#include <rise_time.pio.h>

// Number of clock cycles per PIO counter increment. Adjust this according
// to the assembly program in rise_time.pio.
#define PIO_CYCLES_PER_COUNTER_INCERMENT 5

void rise_time_init(uint32_t baud_rate, uint lo_pin, uint hi_pin,
                    uint rise_count_limit, void (*callback)(void),
                    PIO *pio_hw, uint *sm) {
    uint offset = 0;
    if (!pio_lib_utils_init_pio(&rise_time_program, pio_hw, sm, &offset)) {
        panic("failed to setup pio");
    }
    rise_time_program_init(*pio_hw, *sm, offset, lo_pin, hi_pin);

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

    // Send rise count limit to TX FIFO.
    pio_sm_put_blocking(*pio_hw, *sm, rise_count_limit);
}

float get_avg_cycles(PIO pio_hw, uint sm, uint rise_count_limit) {
    uint32_t rise_time_limit = rise_count_limit;
    uint32_t x = rise_time_program_recv(pio_hw, sm);
    return (float)PIO_CYCLES_PER_COUNTER_INCERMENT * x / rise_time_limit;
}
