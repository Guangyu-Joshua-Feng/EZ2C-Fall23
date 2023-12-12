#include "uint32_array.h"

#include <pico/stdlib.h>

int uint32_array_push_back(uint32_array_t *array, uint32_t val) {
    if (array->size >= UINT32_ARRAY_SIZE) {
        return -1;
    }
    array->buf[array->size] = val;
    return array->size++;
}

int uint32_array_clear(uint32_array_t *array) {
    array->size = 0;
}
