/*
 * cs10.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

static __sfr __at MM58167A_THOUS_S _MM58167A_THOUS_S;

uint8_t timer_cs10(void) {
    return _MM58167A_THOUS_S;
}
