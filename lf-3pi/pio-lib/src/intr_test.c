#include <hardware/gpio.h>
#include <hardware/pio.h>
#include <intr.pio.h>
#include <intr_test.h>
#include <pico/stdlib.h>

#define LED_PIN 16

static state;
static PIO pio;
static uint sm;
static uint offset;
static int8_t pio_irq;

static bool init_pio(const pio_program_t *program, PIO *pio_hw, uint *sm,
                     uint *offset);
static void link_available_irq();
static void pio_irq_func();

void intr_test_start() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    if (!init_pio(&intr_program, &pio, &sm, &offset)) {
        panic("failed to setup pio");
    }
    intr_program_init(pio, sm, offset, 15);
    link_available_irq();

    // Enable interrupt
    irq_set_exclusive_handler(pio_irq, pio_irq_func);
    irq_set_enabled(pio_irq, true);
    const uint irq_index = pio_irq - ((pio == pio0) ? PIO0_IRQ_0 : PIO1_IRQ_0);
    pio_set_irqn_source_enabled(pio, irq_index, pis_interrupt0 + sm,
                                true);
}

// Find a free pio and state machine and load the program into it.
// Returns false if this fails
static bool init_pio(const pio_program_t *program, PIO *pio_hw, uint *sm,
                     uint *offset) {
    // Find a free pio
    *pio_hw = pio0;
    if (!pio_can_add_program(*pio_hw, program)) {
        *pio_hw = pio1;
        if (!pio_can_add_program(*pio_hw, program)) {
            *offset = -1;
            return false;
        }
    }
    *offset = pio_add_program(*pio_hw, program);

    // Find a state machine
    *sm = (int8_t)pio_claim_unused_sm(*pio_hw, false);
    return *sm >= 0;
}

static void link_available_irq() {
    // Find a free irq
    static_assert(PIO0_IRQ_1 == PIO0_IRQ_0 + 1 && PIO1_IRQ_1 == PIO1_IRQ_0 + 1,
                  "");
    pio_irq = (pio == pio0) ? PIO0_IRQ_0 : PIO1_IRQ_0;
    if (irq_get_exclusive_handler(pio_irq)) {
        pio_irq++;
        if (irq_get_exclusive_handler(pio_irq)) {
            panic("All IRQs are in use");
        }
    }
}

static void pio_irq_func() {
    static bool on = false;
    for (int i = 0; i < 4; ++i) {
        if (pio_interrupt_get(pio, i)) {
            gpio_put(LED_PIN, on = !on);
            pio_interrupt_clear(pio, i);
        }
    }
    for (volatile int i = 0; i < 10000000; ++i);
}
