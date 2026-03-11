/*
 * _conio_init.c
 *
 * Lazy conio initialization for libpartner.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include <stdlib.h>

#include "common.h"

void scn2674_cache_rows(void);
static const uint8_t conio_sio1a_wr1_restore = 0x1c;

void _conio_exit(void) {
    _serial_port_out(Z80SIO1_CTRL_A, 0x01);
    _serial_port_out(Z80SIO1_CTRL_A, conio_sio1a_wr1_restore);
}

void _conio_init(void) {
    atexit(_conio_exit);

    /* Force SIO 1 channel A into polling mode so keyboard reads stay raw. */
    _serial_port_out(Z80SIO1_CTRL_A, 0x01);
    _serial_port_out(Z80SIO1_CTRL_A, 0x04);

    scn2674_cache_rows();

    _ti.attr = 0;
    _ti.screenheight = 26;
    gettextinfo(&_ti);
}
