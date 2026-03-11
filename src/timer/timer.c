/*
 * timer.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

int16_t timer(void) {
    return (int16_t)(timer_ms() / 10u);
}
