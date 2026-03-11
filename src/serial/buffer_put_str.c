/*
 * buffer_put_str.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_buffer_put_str(sio_buffer *buffer, const uint8_t *str) {
    const uint8_t *ptr;

    for (ptr = str; *ptr != 0; ptr++) {
        if (!serial_buffer_put_ch(buffer, *ptr)) {
            return false;
        }
    }
    return true;
}
