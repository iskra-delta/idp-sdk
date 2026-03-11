/*
 * rdchat.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

void rdchat(char *c, unsigned char *attr) {
    avdc_getchar(c, attr);
}
