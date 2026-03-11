/*
 * cputs.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

int cputs(const char *s) {
    int len = 0;

    while (*s) {
        int x;
        int y;
        char ch = *s++;

        if (ch == '\r') {
            gotoxy(0, wherey());
            len++;
            continue;
        }

        if (ch == '\n') {
            y = wherey();
            if (y >= 0 && y < _ti.screenheight - 1) {
                gotoxy(0, y + 1);
            } else {
                _ti.curx = 0xff;
                _ti.cury = 0xff;
            }
            len++;
            continue;
        }

        x = wherex();
        y = wherey();
        if (x < 0 || y < 0 || x >= _ti.screenwidth) {
            break;
        }

        gotoxy(x, y);
        scn2674_putchar(ch, _ti.attr);

        if (x < _ti.screenwidth - 1) {
            gotoxy(x + 1, y);
        } else {
            _ti.curx = 0xff;
            _ti.cury = 0xff;
        }

        len++;
    }

    return len;
}
