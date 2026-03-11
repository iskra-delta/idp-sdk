/*
 * done.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include <stdlib.h>

#include "common.h"

void mouse_done(mouse_t *mouse) {
    if (!mouse) {
        return;
    }
    if (mouse->serial) {
        serial_done(mouse->serial);
    }
    free(mouse);
}
