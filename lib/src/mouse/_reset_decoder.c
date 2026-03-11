/*
 * _reset_decoder.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void _mouse_reset_decoder(mouse_t *mouse) {
    mouse->x = 0;
    mouse->y = 0;
    mouse->dx = 0;
    mouse->dy = 0;
    mouse->buttons = 0;
    mouse->count = 0;
    mouse->synced = false;
}
