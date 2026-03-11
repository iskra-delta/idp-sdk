/*
 * timer_diff.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

int16_t timer_diff(uint16_t timer_start, uint16_t timer_offset) {
    uint16_t now = (uint16_t)timer();
    uint16_t base = timer_start + timer_offset;

    if (now >= timer_start) {
        return (int16_t)(now - base);
    }

    return (int16_t)((now + 6000u) - base);
}
