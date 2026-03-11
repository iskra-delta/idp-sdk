/*
 * wherex.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

int wherex(void) {
    if (_ti.curx == 0xff) {
        uint8_t y = wherey();
        if (y != 0xff) {
            _ti.curx = scn2674_cursor_addr() - scn2674_rowptr(y);
        }
    }
    return _ti.curx;
}
