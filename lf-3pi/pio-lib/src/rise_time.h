#ifndef PIO_LIB_RISE_TIME_H_
#define PIO_LIB_RISE_TIME_H_

void rise_time_start(uint32_t baud_rate, uint lo_pin, uint hi_pin);

float get_avg_cycles();

#endif  // PIO_LIB_RISE_TIME_H_
