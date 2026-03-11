/*
 * buffer_empty.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_buffer_empty(sio_buffer *buffer) {
    return buffer->count == 0;
}
