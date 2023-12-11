#pragma once

#include <pico/stdlib.h>

#define CIRCULAR_BUFFER_SIZE 30
#define EXTENDED_CIRCULAR_BUFFER_SIZE 1000

typedef struct CircularBuffer {
    float buf[CIRCULAR_BUFFER_SIZE];
    int size;  // [0, CIRCULAR_BUFFER_SIZE]
    int next;  // [0, CIRCULAR_BUFFER_SIZE)
} circular_buffer_t;

typedef struct ExtendedCircularBuffer {
    uint32_t buf[EXTENDED_CIRCULAR_BUFFER_SIZE];
    int size;
    int next;
    float avg;
} extended_circular_buffer_t;

float circular_buffer_get_avg(const circular_buffer_t *buf);
int circular_buffer_push(circular_buffer_t *buf, float val);
int circular_buffer_clear(circular_buffer_t *buf);

int extended_circular_buffer_push(extended_circular_buffer_t *buf,
                                  uint32_t val);
int extended_circular_buffer_clear(extended_circular_buffer_t *buf);
