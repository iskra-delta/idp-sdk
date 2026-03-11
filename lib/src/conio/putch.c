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
    unsigned char x;
    unsigned char y;

    if (ch == '\r') {
        y = _ti.cury;
        if (y == 0xff) {
            y = (unsigned char)wherey();
        }
        if (y != 0xff) {
            gotoxy(0, y);
        }
        return c;
    }
    if (ch == '\n') {
        y = _ti.cury;
        if (y == 0xff) {
            y = (unsigned char)wherey();
        }
        if (y != 0xff && y < _ti.screenheight - 1) {
            gotoxy(0, y + 1);
        } else {
            _ti.curx = 0xff;
            _ti.cury = 0xff;
        }
        return c;
    }
    x = _ti.curx;
    if (x == 0xff) {
        x = (unsigned char)wherex();
    }
    if (x == 0xff || x >= _ti.screenwidth) {
        return c;
    }
    if (x < _ti.screenwidth - 1) {
        scn2674_putchar(ch, _ti.attr);
        _ti.curx = x + 1;
    } else {
        scn2674_putchar(ch, _ti.attr);
        _ti.curx = 0xff;
        _ti.cury = 0xff;
    }
    return c;
}
