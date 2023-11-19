#include <hardware/clocks.h>
#include <hardware/pio.h>
#include <pico/stdlib.h>
#include <pio_lib_utils.h>
#include <rise_time.h>
#include <rise_time.pio.h>

#define PIO_LO_THRESHOLD_PIN 20
#define PIO_HI_THRESHOLD_PIN 21

static PIO pio_hw;
static uint sm;
static uint offset;
static int8_t pio_irq;

static void nvic_pio_irq_handler();
static void irq_handler_helper(int i);
static uint32_t get_rise_count_limit();

void rise_time_start() {
    if (!pio_lib_utils_init_pio(&rise_time_program, &pio_hw, &sm, &offset)) {
        panic("failed to setup pio");
    }
    rise_time_program_init(pio, sm, offset, PIO_LO_THRESHOLD_PIN,
                           PIO_HI_THRESHOLD_PIN);

    // Set up IRQ.
    int8_t nvic_pio_irq = pio_lib_utils_find_available_nvic_irq(pio_hw);
    if (nvic_pio_irq < 0) {
        panic("failed to find available nvic irq for pio");
    }
    irq_set_exclusive_handler(nvic_pio_irq, &nvic_pio_irq_handler);
    irq_set_enabled(nvic_pio_irq, true);
    uint index = pio_lib_utils_get_nvic_pio_irq_index(nvic_pio_irq);
    pio_set_irqn_source_enabled(pio, index, pis_interrupt0 + sm, true);
    pio_set_irqn_source_enabled(pio, index, pis_interrupt1 + sm, true);
    pio_set_irqn_source_enabled(pio, index, pis_interrupt2 + sm, true);

    // Send rise count limit to TX FIFO.
    pio_sm_put_blocking(pio_hw, sm, get_rise_count_limit());
}

static void nvic_pio_irq_handler() {
    static bool on = false;
    for (int i = 0; i < 4; ++i) {
        if (pio_interrupt_get(pio, i)) {
            irq_handler_helper(i);
        }
    }
}

static void irq_handler_helper(int i) {
    switch (i) {
        case 0:
            uint32_t x = rise_time_program_recv(pio_hw, sm);
            float avg_cycles = 3.0f * (x - 1) / 10;
            printf("average rise time: %f cycles\n", avg_cycles);
            break;

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
    pio_interrupt_get(pio_hw, i);
}

static uint32_t get_rise_count_limit() {
    uint32_t curr_clock = clock_get_hz(clk_sys);
    return 10;  // TODO: modify this when ready to use.
}
