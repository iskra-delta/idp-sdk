/*
 * timer_ms.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

uint16_t timer_ms(void) {
    rtc_time_t t1;
    rtc_time_t t2;
    uint8_t cs10 = timer_cs10();
    uint16_t ms;

    rtc_get(&t1);
    rtc_get(&t2);

    if (t1.hsec == t2.hsec) {
        ms = (uint16_t)t1.hsec * 10u + (uint16_t)bcd2bin(cs10 >> 4);
    } else {
        ms = (uint16_t)t2.hsec * 10u;
    }

    if (t1.sec == t2.sec) {
        return (uint16_t)t1.sec * 1000u + ms;
    }

    return (uint16_t)t2.sec * 1000u;
}
