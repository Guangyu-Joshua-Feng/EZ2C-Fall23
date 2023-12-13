#pragma once

#include <pico/stdlib.h>

#define UINT32_ARRAY_SIZE 1000

typedef struct Uint32Array {
    uint32_t buf[UINT32_ARRAY_SIZE];
    int size;
} uint32_array_t;

int uint32_array_push_back(uint32_array_t *array, uint32_t val);

int uint32_array_clear(uint32_array_t *array);
