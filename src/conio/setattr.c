/*
 * setattr.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

void setattr(unsigned char attr) {
    _ti.attr = attr;
}
