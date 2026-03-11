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
        const char *start;
        unsigned char limit;
        unsigned char run = 0;
        unsigned char x;
        unsigned char y;
        char ch = *s++;

        if (ch == '\r') {
            y = _ti.cury;
            if (y == 0xff) {
                y = (unsigned char)wherey();
            }
            if (y != 0xff) {
                gotoxy(0, y);
            }
            len++;
            continue;
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
            len++;
            continue;
        }

        x = _ti.curx;
        if (x == 0xff) {
            x = (unsigned char)wherex();
        }
        y = _ti.cury;
        if (y == 0xff) {
            y = (unsigned char)wherey();
        }
        if (x == 0xff || y == 0xff || x >= _ti.screenwidth) {
            break;
        }

        start = s - 1;
        limit = _ti.screenwidth - x;
        while (start[run] &&
            start[run] != '\r' &&
            start[run] != '\n' &&
            run < limit) {
            run++;
        }

        scn2674_puts_burst(start, run, _ti.attr);
        s = start + run;

        if (run < limit) {
            _ti.curx = x + run;
        } else {
            _ti.curx = 0xff;
            _ti.cury = 0xff;
        }

        len += run;
    }

    return len;
}
