/*
 * timer.h
 *
 * Top-level timer helpers for libpartner.
 *
 * NOTES:
 *  - Uses the Partner RTC subsecond and second registers directly.
 *  - `timer()` returns 1/100 second ticks within a 60 second window.
 *  - `timer_ms()` returns milliseconds within a 60 second window.
 *  - `timer_diff()` computes a wrapped difference with caller-supplied
 *    start and offset values; no internal timer state is cached.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#ifndef __PARTNER_TIMER_H__
#define __PARTNER_TIMER_H__

#include <stdint.h>

/* Read the current timer value in milliseconds within a 60 second window. */
uint16_t timer_ms(void);

/* Read the current timer value in 1/100 second ticks within a 60 second window. */
int16_t timer(void);

/* Compute wrapped difference from a previous timer value and offset. */
int16_t timer_diff(uint16_t timer_start, uint16_t timer_offset);

#endif /* __PARTNER_TIMER_H__ */
