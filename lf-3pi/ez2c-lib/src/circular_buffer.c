#include "circular_buffer.h"

float circular_buffer_get_avg(const circular_buffer_t *buf) {
    // TODO: this function can be further optimized.
    float sum = 0.0f;
    for (int i = 0; i < buf->size; ++i) {
        sum += buf->buf[i];
    }
    return sum / buf->size;
}

int circular_buffer_push(circular_buffer_t *buf, float val) {
    buf->buf[buf->next] = 0;
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
