/*
 * _buffer_alloc_internal.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include <stdlib.h>

#include "common.h"

void _serial_buffer_alloc_internal(sio_buffer *buffer, uint16_t size) {
    buffer->values = malloc(size);
    buffer->size = size;
}
