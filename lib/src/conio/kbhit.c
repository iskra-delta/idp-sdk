/*
 * kbhit.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

int kbhit(void) {
    if (_conio_kbhit_use_bdos)
        return (unsigned char)bdos(C_RAWIO, 0x00ff);
    return (unsigned char)kbd_poll_key();
}

void kbhit_set_bdos(bool use_bdos) {
    _conio_kbhit_use_bdos = use_bdos;
}
