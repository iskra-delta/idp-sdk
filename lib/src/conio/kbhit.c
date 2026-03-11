/*
 * kbhit.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

int kbhit(void) {
    return (unsigned char)kbd_get_key();
}
