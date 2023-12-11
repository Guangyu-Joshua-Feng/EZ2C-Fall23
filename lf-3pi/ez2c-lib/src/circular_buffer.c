#include "circular_buffer.h"

#include <pico/stdlib.h>

float circular_buffer_get_avg(const circular_buffer_t *buf) {
    // TODO: this function can be further optimized.
    float sum = 0.0f;
    for (int i = 0; i < buf->size; ++i) {
        sum += buf->buf[i];
    }
    return sum / buf->size;
}

int circular_buffer_push(circular_buffer_t *buf, float val) {
    buf->buf[buf->next] = val;
    buf->next = (buf->next + 1) % CIRCULAR_BUFFER_SIZE;
    if (buf->size < CIRCULAR_BUFFER_SIZE) {
        ++buf->size;
    }
    return buf->next;
}

int circular_buffer_clear(circular_buffer_t *buf) {
    buf->size = 0;
    buf->next = 0;
}

int extended_circular_buffer_push(extended_circular_buffer_t *buf,
                                  uint32_t val) {
    uint32_t evicted = buf->buf[buf->next];
    buf->buf[buf->next] = val;
    buf->next = (buf->next + 1) % EXTENDED_CIRCULAR_BUFFER_SIZE;
    if (buf->size < EXTENDED_CIRCULAR_BUFFER_SIZE) {
        buf->avg = (buf->avg * buf->size + val) / (buf->size + 1);
        ++buf->size;
    } else {
        buf->avg += (val - evicted) / buf->size;
    }
    return buf->next;
}

int extended_circular_buffer_clear(extended_circular_buffer_t *buf) {
    buf->size = 0;
    buf->next = 0;
    buf->avg = 0.0f;
}
