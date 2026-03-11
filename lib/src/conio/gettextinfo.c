/*
 * gettextinfo.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

static __sfr __at 0xac _SETUP_WIDTH;

void gettextinfo(struct text_info *r) {
    _ti.screenwidth = _SETUP_WIDTH - 1;
    r->curx = wherex();
    r->cury = wherey();
    r->attr = _ti.attr;
    r->screenheight = _ti.screenheight;
    r->screenwidth = _ti.screenwidth;
}
