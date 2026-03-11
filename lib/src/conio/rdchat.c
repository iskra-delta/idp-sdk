/*
 * rdchat.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 */
#include "common.h"

void rdchat(char *c, unsigned char *attr) {
    scn2674_getchar(c, attr);
}
