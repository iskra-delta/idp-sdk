/*
 * _feed_microsoft.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void _mouse_feed_microsoft(mouse_t *mouse, uint8_t b) {
    uint8_t buttons;
    int8_t dx;
    int8_t dy;

    if (mouse->count == 0) {
        if ((b & 0x40) == 0) {
            return;
        }
        mouse->packet[mouse->count++] = b;
        mouse->synced = true;
        return;
    }

    if ((b & 0x40) != 0) {
        mouse->packet[0] = b;
        mouse->count = 1;
        mouse->synced = true;
        return;
    }

    if (mouse->count < 3) {
        mouse->packet[mouse->count++] = b;
    } else if (mouse->type == MOUSE_GENIUS_C7) {
        mouse->buttons &= (uint8_t)~MOUSE_BUTTON_MIDDLE;
        if ((b & 0x20) != 0) {
            mouse->buttons |= MOUSE_BUTTON_MIDDLE;
        }
        mouse->count = 0;
        mouse->synced = false;
        return;
    } else {
        mouse->count = 0;
        mouse->synced = false;
        return;
    }

    if (mouse->count != 3) {
        return;
    }

    buttons = 0;
    if ((mouse->packet[0] & 0x20) != 0) {
        buttons |= MOUSE_BUTTON_LEFT;
    }
    if ((mouse->packet[0] & 0x10) != 0) {
        buttons |= MOUSE_BUTTON_RIGHT;
    }
    if (mouse->type == MOUSE_GENIUS_C7) {
        buttons |= (mouse->buttons & MOUSE_BUTTON_MIDDLE);
    }

    dx = (int8_t)(((mouse->packet[0] & 0x03) << 6) | (mouse->packet[1] & 0x3F));
    dy = (int8_t)(((mouse->packet[0] & 0x0C) << 4) | (mouse->packet[2] & 0x3F));

    _mouse_apply_packet(mouse, dx, dy, buttons);
    mouse->count = (mouse->type == MOUSE_GENIUS_C7) ? 3 : 0;
    mouse->synced = (mouse->type == MOUSE_GENIUS_C7);
}
