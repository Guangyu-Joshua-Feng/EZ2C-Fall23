#pragma once

#define CIRCULAR_BUFFER_SIZE 30

typedef struct CircularBuffer {
    float buf[CIRCULAR_BUFFER_SIZE];
    int size;  // [0, CIRCULAR_BUFFER_SIZE]
    int next;  // [0, CIRCULAR_BUFFER_SIZE)
} circular_buffer_t;

float circular_buffer_get_avg(const circular_buffer_t *buf);
int circular_buffer_push(circular_buffer_t *buf, float val);
int circular_buffer_clear(circular_buffer_t *buf);
