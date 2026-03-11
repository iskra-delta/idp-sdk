/*
 * buffer_peek.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

uint8_t serial_buffer_peek(sio_buffer *buffer, uint16_t idx) {
    if (buffer->count <= idx) {
        return 0;
    }
    idx += buffer->get_ptr;
    idx %= buffer->size;
    return buffer->values[idx];
}
