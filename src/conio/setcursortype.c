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
        avdc_hide_cursor();
    } else {
        avdc_show_cursor();
    }
}
