#ifndef PIO_LIB_RISE_TIME_H_
#define PIO_LIB_RISE_TIME_H_

void rise_time_init(uint32_t baud_rate, uint lo_pin, uint hi_pin,
                    uint rise_count_limit, void (*callback)(void),
                    PIO *pio_hw, uint *sm);

float get_avg_cycles(PIO pio_hw, uint sm, uint rise_count_limit);

#endif  // PIO_LIB_RISE_TIME_H_
