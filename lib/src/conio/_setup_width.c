/*
 * _setup_width.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

static __sfr __at 0xac _SETUP_WIDTH;

uint8_t _conio_setup_width(void) {
    return _SETUP_WIDTH;
}
