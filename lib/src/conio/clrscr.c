/*
 * clrscr.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

void clrscr(void) {
    scn2674_cls();
    _ti.attr = 0;
    _ti.curx = 0;
    _ti.cury = 0;
}
