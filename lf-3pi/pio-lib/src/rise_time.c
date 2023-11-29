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

static uint32_t global_baud;
static PIO pio_hw;
static uint sm;
static uint offset;
static int8_t pio_irq;
static float avg_cycles;

static void nvic_pio_irq_handler();
static void irq_handler_helper(int i);
static inline uint32_t get_rise_count_limit(uint32_t baud_rate);

void rise_time_start(uint32_t baud_rate, uint lo_pin, uint hi_pin) {
    if (!pio_lib_utils_init_pio(&rise_time_program, &pio_hw, &sm, &offset)) {
        panic("failed to setup pio");
    }
    rise_time_program_init(pio_hw, sm, offset, lo_pin, hi_pin);

    // Set up IRQ.
    int8_t nvic_pio_irq = pio_lib_utils_find_available_nvic_irq(pio_hw);
    if (nvic_pio_irq < 0) {
        panic("failed to find available nvic irq for pio");
    }
    irq_set_exclusive_handler(nvic_pio_irq, &nvic_pio_irq_handler);
    irq_set_enabled(nvic_pio_irq, true);
    uint index = pio_lib_utils_get_nvic_pio_irq_index(pio_hw, nvic_pio_irq);
    pio_set_irqn_source_enabled(pio_hw, index, pis_interrupt0 + sm, true);
    pio_set_irqn_source_enabled(pio_hw, index, pis_interrupt1 + sm, true);
    pio_set_irqn_source_enabled(pio_hw, index, pis_interrupt2 + sm, true);

    // Send rise count limit to TX FIFO.
    global_baud = baud_rate;
    pio_sm_put_blocking(pio_hw, sm, get_rise_count_limit(global_baud));
}

float get_avg_cycles() {
    return avg_cycles;
}

static void nvic_pio_irq_handler() {
    static bool on = false;
    for (int i = 0; i < 4; ++i) {
        if (pio_interrupt_get(pio_hw, i)) {
            irq_handler_helper(i);
        }
    }
}

static void irq_handler_helper(int i) {
    switch (i) {
        case 0: {
            uint32_t rise_time_limit = get_rise_count_limit(global_baud);
            uint32_t x = rise_time_program_recv(pio_hw, sm);
            avg_cycles =
                (float)PIO_CYCLES_PER_COUNTER_INCERMENT * x / rise_time_limit;
            printf("PIO: %f cycles\n", avg_cycles);
            pio_sm_put_blocking(pio_hw, sm, rise_time_limit - 1);
            break;
        }
        case 1:
            printf("resolution warning\n");
            break;

        case 2:
            printf("capacitance warning\n");
            break;

        default:
            printf("unknown irq flag warning\n");
            break;
    }
    pio_interrupt_clear(pio_hw, i);
}

static inline uint32_t get_rise_count_limit(uint32_t baud_rate) {
    // static uint32_t min_baud_rate = 2000;
    // return baud_rate < min_baud_rate ? min_baud_rate : baud_rate;
    // TODO: decide whether or not to get rid of baud_rate
    return 1000;
}
