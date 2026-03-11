/*
 * platform.c
 *
 * Partner platform hooks for libcpm3-z80.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 11.03.2026   tstih
 *
 */
#include <platform.h>

#include <partner/clock.h>

void _libinit(void) {
    libplatform = PLATFORM_NAME_STR;
    nltype = NL_CRLF;
}

void msleep(int millisec) {
    while (millisec > 0) {
        uint16_t chunk = (millisec > 30000) ? 30000u : (uint16_t)millisec;
        uint16_t start = timer_ms();

        while ((uint16_t)timer_diff(start, 0) < chunk) {
        }

        millisec -= (int)chunk;
    }
}
