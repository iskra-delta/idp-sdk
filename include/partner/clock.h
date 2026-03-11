/*
 * clock.h
 *
 * Public clock and BCD services.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#ifndef __PARTNER_CLOCK_H__
#define __PARTNER_CLOCK_H__

#include <stdint.h>

typedef struct rtc_time_s {
    uint8_t hsec;
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t wday;
    uint8_t mday;
    uint8_t month;
    uint8_t year;
} rtc_time_t;

/* Convert an 8-bit binary value to packed BCD. */
extern uint8_t bin2bcd(uint8_t bin);

/* Convert an 8-bit packed BCD value to binary. */
extern uint8_t bcd2bin(uint8_t bcd);

/* Read the current timer value in milliseconds within a 60 second window. */
extern uint16_t timer_ms(void);

/* Read the current timer value in 1/100 second ticks within a 60 second window. */
extern int16_t timer(void);

/* Compute wrapped difference from a previous timer value and offset. */
extern int16_t timer_diff(uint16_t timer_start, uint16_t timer_offset);

/* Reset the RTC counters and restart timekeeping. */
extern void rtc_reset(void);

/* Reset the RTC NVRAM area. */
extern void rtc_reset_nvram(void);

/* Read the current RTC date and time into the supplied structure. */
extern void rtc_get(rtc_time_t *t);

/* Write the supplied date and time to the RTC. */
extern void rtc_set(const rtc_time_t *t);

#endif /* __PARTNER_CLOCK_H__ */
