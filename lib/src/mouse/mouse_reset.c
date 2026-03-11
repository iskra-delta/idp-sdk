/*
 * reset.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void mouse_reset(mouse_t *mouse) {
    _mouse_reset_decoder(mouse);
}
