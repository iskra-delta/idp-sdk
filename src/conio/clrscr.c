/*
 * clrscr.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

void clrscr(void) {
    avdc_cls();
    _ti.attr = 0;
    _ti.screenwidth = conio_setup_width() - 1;
    _ti.curx = 0;
    _ti.cury = 0;
}
