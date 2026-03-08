/*
 * timer.c
 *
 * Top-level timer helpers for libpartner.
 *
 * NOTES:
 *  - Reuses the Partner RTC service for seconds and 1/100 second reads.
 *  - Reads the 1/1000 second register directly only for millisecond
 *    precision, because rtc_get() does not expose that nibble.
 *  - The return range wraps every 60 seconds.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#include <stdint.h>

#include <partner/bcd.h>
#include <partner/hw/partner/rtc.h>
#include <partner/timer.h>

__sfr __at MM58167A_THOUS_S _MM58167A_THOUS_S;

/* Read milliseconds, retrying across subsecond / second rollover. */
uint16_t timer_ms(void) {
    rtc_time_t t1;
    rtc_time_t t2;
    uint8_t cs10 = _MM58167A_THOUS_S;
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

/* Read 1/100 second ticks. */
int16_t timer(void) {
    return (int16_t)(timer_ms() / 10u);
}

/* Return wrapped difference from a caller-supplied start and offset. */
int16_t timer_diff(uint16_t timer_start, uint16_t timer_offset) {
    uint16_t now = (uint16_t)timer();
    uint16_t base = timer_start + timer_offset;

    if (now >= timer_start) {
        return (int16_t)(now - base);
    }

    return (int16_t)((now + 6000u) - base);
}
