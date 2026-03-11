/*
 * buffer_put_ch.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_buffer_put_ch(sio_buffer *buffer, uint8_t ch) {
    if (buffer->count == buffer->size) {
        return false;
    }
    buffer->values[buffer->put_ptr++] = ch;
    buffer->count++;
    if (buffer->put_ptr == buffer->size) {
        buffer->put_ptr = 0;
    }
    return true;
}
