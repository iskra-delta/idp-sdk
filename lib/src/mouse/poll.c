/*
 * poll.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void mouse_poll(mouse_t *mouse) {
    uint8_t b;

    mouse->dx = 0;
    mouse->dy = 0;

    (void)serial_exchange(mouse->serial);
    while (!serial_buffer_empty(&mouse->serial->buffer_in)) {
        b = serial_buffer_get_ch(&mouse->serial->buffer_in);
        switch (mouse->type) {
        case MOUSE_MICROSOFT:
        case MOUSE_GENIUS_C7:
            _mouse_feed_microsoft(mouse, b);
            break;
        case MOUSE_MOUSESYSTEMS:
            _mouse_feed_mousesystems(mouse, b);
            break;
        }
    }
}
