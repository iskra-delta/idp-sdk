/*
 * _apply_packet.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void _mouse_apply_packet(mouse_t *mouse, int8_t dx, int8_t dy, uint8_t buttons) {
    mouse->dx += dx;
    mouse->dy += dy;
    mouse->x += dx;
    mouse->y += dy;
    mouse->buttons = buttons;
}
