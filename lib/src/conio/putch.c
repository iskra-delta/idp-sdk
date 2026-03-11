/*
 * putch.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

int putch(int c) {
    char ch = c;

    if (ch == '\r') {
        gotoxy(0, wherey());
        return c;
    }
    if (ch == '\n') {
        int y = wherey();

        if (y >= 0 && y < _ti.screenheight - 1) {
            gotoxy(0, y + 1);
        } else {
            _ti.curx = 0xff;
            _ti.cury = 0xff;
        }
        return c;
    }
    if (wherex() < _ti.screenwidth - 1) {
        int x = wherex();
        int y = wherey();

        scn2674_putchar(ch, _ti.attr);
        gotoxy(x + 1, y);
    } else if (wherex() == _ti.screenwidth - 1) {
        scn2674_putchar(ch, _ti.attr);
    }
    return c;
}
