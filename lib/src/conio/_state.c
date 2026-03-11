/*
 * _state.c
 *
 * Shared conio state for libpartner.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

struct text_info _ti = {
    0x00,   /* attr */
    26,     /* screenheight */
    0x00,   /* screenwidth */
    0xff,   /* curx */
    0xff    /* cury */
};
