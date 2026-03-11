/*
 * wherey.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

int wherey(void) {
    if (_ti.cury == 0xff) {
        uint16_t curaddr = avdc_cursor_addr();
        unsigned char row;

        for (row = 0; row < 26; row++) {
            uint16_t rowaddr = avdc_rowptr(row);
            if (curaddr >= rowaddr && curaddr < rowaddr + 132) {
                _ti.cury = row;
                return row;
            }
        }
    }
    return _ti.cury;
}
