/*
 * gettextinfo.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

void gettextinfo(struct text_info *r) {
    r->curx = wherex();
    r->cury = wherey();
    r->attr = _ti.attr;
    r->screenheight = _ti.screenheight;
    r->screenwidth = _ti.screenwidth;
}
