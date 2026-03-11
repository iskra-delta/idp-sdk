/*
 * rtc.h
 *
 * Internal MM58167A RTC hardware map for Partner.
 *
 * MM58167A real-time clock map on Partner.
 *
 * Time/date registers are stored in packed BCD and accessed through I/O
 * ports. The SDK uses these ports for RTC reads/writes and for deriving the
 * short-interval timer helpers.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */

#ifndef LIBPARTNER_HW_RTC_H
#define LIBPARTNER_HW_RTC_H

/* 1/1000 second digit register used to refine timer_ms(). */
#define MM58167A_THOUS_S            0xA0
/* 1/100 second register. */
#define MM58167A_HUNDR_S            0xA1
/* Seconds register. */
#define MM58167A_SECOND             0xA2
/* Minutes register. */
#define MM58167A_MINUTE             0xA3
/* Hours register. */
#define MM58167A_HOUR               0xA4
/* Weekday register. */
#define MM58167A_WDAY               0xA5
/* Day-of-month register. */
#define MM58167A_MDAY               0xA6
/* Month register. */
#define MM58167A_MONTH              0xA7

/* Partner stores a synthetic two-digit year in this RTC/NVRAM slot. */
#define MM58167A_YEAR               0xA9

/* Interrupt-status register. */
#define MM58167A_INT_STATUS         0xB0
/* Interrupt-control/mask register. */
#define MM58167A_INT_CONTROL        0xB1
/* Counter reset strobe. */
#define MM58167A_RESET_COUNTER      0xB2
/* NVRAM/reset-flags strobe. */
#define MM58167A_RESET_NVRAM        0xB3
/* General RTC status register. */
#define MM58167A_STATUS             0xB4
/* Start/stop or go register used when programming the clock. */
#define MM58167A_GO                 0xB5
/* Test register reserved for chip diagnostics. */
#define MM58167A_TEST               0xBF

#endif
