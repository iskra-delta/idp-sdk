/*
 * setcursortype.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

void setcursortype(int cur_t) {
    if (cur_t == NOCURSOR) {
        scn2674_hide_cursor();
    } else {
        scn2674_show_cursor();
    }
}
