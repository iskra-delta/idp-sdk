/*
 * buffer_put.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_buffer_put(sio_buffer *buffer, uint16_t len, const uint8_t *values) {
    uint16_t i;

    for (i = 0; i < len; i++) {
        if (!serial_buffer_put_ch(buffer, values[i])) {
            return false;
        }
    }
    return true;
}
