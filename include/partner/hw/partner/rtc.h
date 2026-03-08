/*
 * rtc.h
 *
 * Partner real-time clock service declarations and MM58167A port map.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#ifndef __PARTNER_RTC_H__
#define __PARTNER_RTC_H__

#include <stdint.h>

/* --- 0xA0-0xA7 - MM58167A time registers (BCD) -------------------------- */
/* 0xA0 - 1/1000 second */
#define MM58167A_THOUS_S            0xA0
/* 0xA1 - 1/100 second */
#define MM58167A_HUNDR_S            0xA1
/* 0xA2 - seconds */
#define MM58167A_SECOND             0xA2
/* 0xA3 - minutes */
#define MM58167A_MINUTE             0xA3
/* 0xA4 - hours */
#define MM58167A_HOUR               0xA4
/* 0xA5 - weekday */
#define MM58167A_WDAY               0xA5
/* 0xA6 - month day */
#define MM58167A_MDAY               0xA6
/* 0xA7 - month */
#define MM58167A_MONTH              0xA7

/* --- 0xA8-0xAF - MM58167A alarm / nvram registers ----------------------- */
/* 0xA9 - fake two-digit year stored in nvram */
#define MM58167A_YEAR               0xA9

/* --- 0xB0-0xBF - MM58167A status / control ------------------------------ */
/* 0xB0 - interrupt status */
#define MM58167A_INT_STATUS         0xB0
/* 0xB1 - interrupt control */
#define MM58167A_INT_CONTROL        0xB1
/* 0xB2 - reset counter */
#define MM58167A_RESET_COUNTER      0xB2
/* 0xB3 - reset nvram flags */
#define MM58167A_RESET_NVRAM        0xB3
/* 0xB4 - status */
#define MM58167A_STATUS             0xB4
/* 0xB5 - go / reset clock */
#define MM58167A_GO                 0xB5
/* 0xBF - chip test */
#define MM58167A_TEST               0xBF

/* Partner RTC date/time in binary form. */
typedef struct rtc_time_s {
    uint8_t hsec;
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t wday;
    uint8_t mday;
    uint8_t month;
    uint8_t year; /* two-digit year */
} rtc_time_t;

/* Reset the running clock before programming new values. */
extern void rtc_reset(void);

/* Reset RTC nvram flags. */
extern void rtc_reset_nvram(void);

/* Read binary date/time from RTC. */
extern void rtc_get(rtc_time_t *t);

/* Write binary date/time to RTC. */
extern void rtc_set(const rtc_time_t *t);

#endif /* __PARTNER_RTC_H__ */
