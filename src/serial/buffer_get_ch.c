/*
 * buffer_get_ch.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

uint8_t serial_buffer_get_ch(sio_buffer *buffer) {
    uint8_t ch;

    if (buffer->count == 0) {
        return 0;
    }
    ch = buffer->values[buffer->get_ptr++];
    buffer->count--;
    if (buffer->get_ptr == buffer->size) {
        buffer->get_ptr = 0;
    }
    return ch;
}
