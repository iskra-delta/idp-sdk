/*
 * _feed_mousesystems.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void _mouse_feed_mousesystems(mouse_t *mouse, uint8_t b) {
    uint8_t buttons;
    int8_t dx;
    int8_t dy;

    if (mouse->count == 0) {
        if ((b & 0xF8) != 0x80) {
            return;
        }
        mouse->packet[mouse->count++] = b;
        mouse->synced = true;
        return;
    }

    if ((b & 0xF8) == 0x80) {
        mouse->packet[0] = b;
        mouse->count = 1;
        mouse->synced = true;
        return;
    }

    if (mouse->count < 5) {
        mouse->packet[mouse->count++] = b;
    }

    if (mouse->count != 5) {
        return;
    }

    buttons = 0;
    if ((mouse->packet[0] & 0x04) == 0) {
        buttons |= MOUSE_BUTTON_LEFT;
    }
    if ((mouse->packet[0] & 0x02) == 0) {
        buttons |= MOUSE_BUTTON_MIDDLE;
    }
    if ((mouse->packet[0] & 0x01) == 0) {
        buttons |= MOUSE_BUTTON_RIGHT;
    }

    dx = (int8_t)((int8_t)mouse->packet[1] + (int8_t)mouse->packet[3]);
    dy = (int8_t)(-((int8_t)mouse->packet[2] + (int8_t)mouse->packet[4]));

    _mouse_apply_packet(mouse, dx, dy, buttons);
    mouse->count = 0;
    mouse->synced = false;
}
