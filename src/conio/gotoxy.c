/*
 * gotoxy.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

void gotoxy(int x, int y) {
    if (x >= 0 && x < _ti.screenwidth && y >= 0 && y < _ti.screenheight) {
        avdc_xy(x, y);
        _ti.curx = x;
        _ti.cury = y;
    } else {
        _ti.curx = 0xff;
        _ti.cury = 0xff;
    }
}
