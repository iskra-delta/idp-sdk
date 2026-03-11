/*
 * buffer_get.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

uint16_t serial_buffer_get(sio_buffer *buffer, uint8_t *dest) {
    uint8_t *p = dest;
    uint16_t count = buffer->count;

    while (!serial_buffer_empty(buffer)) {
        *(p++) = serial_buffer_get_ch(buffer);
    }
    return count;
}
