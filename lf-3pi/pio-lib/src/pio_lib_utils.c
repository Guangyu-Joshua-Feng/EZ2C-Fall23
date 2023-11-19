#include <pio_lib_utils.h>

// Finds a free pio and state machine and load the program into it.
// Returns false if this fails
// Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
// SPDX-License-Identifier: BSD-3-Clause
// Adapted from pico-examples/pio/uart_rx/uart_rx_intr.c.
// Modified return statement.
bool pio_lib_utils_init_pio(const pio_program_t *program, PIO *pio_hw, uint *sm,
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

// Finds a free NVIC IRQ available for PIO and returns its index.
// Returns -1 if all IRQs are taken.
// Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
// SPDX-License-Identifier: BSD-3-Clause
// Adapted from pico-examples/pio/uart_rx/uart_rx_intr.c.
int8_t pio_lib_utils_find_available_nvic_irq(const PIO pio_hw) {
    static_assert(PIO0_IRQ_1 == PIO0_IRQ_0 + 1 && PIO1_IRQ_1 == PIO1_IRQ_0 + 1,
                  "");

    int8_t nvic_pio_irq = (pio_hw == pio0) ? PIO0_IRQ_0 : PIO1_IRQ_0;
    if (irq_get_exclusive_handler(nvic_pio_irq)) {
        nvic_pio_irq++;
        if (irq_get_exclusive_handler(nvic_pio_irq)) {
            return -1;
        }
    }

    return nvic_pio_irq;
}

uint pio_lib_utils_get_nvic_pio_irq_index(int8_t nvic_pio_irq) {
    static_assert(PIO0_IRQ_1 == PIO0_IRQ_0 + 1 && PIO1_IRQ_1 == PIO1_IRQ_0 + 1,
                  "");

    return nvic_pio_irq - ((pio == pio0) ? PIO0_IRQ_0 : PIO1_IRQ_0);
}
