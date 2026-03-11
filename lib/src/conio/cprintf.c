/*
 * cprintf.c
 *
 * Minimal formatted console output for libpartner.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "common.h"

static int cprintf_emit_repeat(char ch, int count) {
    int written = 0;

    while (count-- > 0) {
        putch(ch);
        written++;
    }

    return written;
}

static int cprintf_emit_string(const char *str, int width, char pad) {
    int len = 0;
    int written = 0;
    const char *p = str;

    if (!str) {
        str = "(null)";
        p = str;
    }

    while (*p++) {
        len++;
    }

    written += cprintf_emit_repeat(pad, width - len);
    written += cputs(str);
    return written;
}

static int cprintf_emit_unsigned(unsigned int value, unsigned int base,
    bool uppercase, int width, char pad) {
    char buf[16];
    int len = 0;
    int written = 0;

    do {
        unsigned int digit = value % base;

        if (digit < 10u) {
            buf[len++] = (char)('0' + digit);
        } else {
            buf[len++] = (char)((uppercase ? 'A' : 'a') + (digit - 10u));
        }

        value /= base;
    } while (value != 0u);

    written += cprintf_emit_repeat(pad, width - len);

    while (len-- > 0) {
        putch(buf[len]);
        written++;
    }

    return written;
}

static int cprintf_emit_signed(int value, int width, char pad) {
    unsigned int magnitude;
    int written = 0;

    if (value < 0) {
        putch('-');
        written++;
        magnitude = (unsigned int)(0u - (unsigned int)value);
        if (width > 0) {
            width--;
        }
    } else {
        magnitude = (unsigned int)value;
    }

    return written + cprintf_emit_unsigned(magnitude, 10u, false, width, pad);
}

static int vcprintf(const char *fmt, va_list ap) {
    int written = 0;

    while (*fmt) {
        int width = 0;
        char pad = ' ';

        if (*fmt != '%') {
            putch(*fmt++);
            written++;
            continue;
        }

        fmt++;
        if (*fmt == '0') {
            pad = '0';
            fmt++;
        }

        while (*fmt >= '0' && *fmt <= '9') {
            width = width * 10 + (*fmt - '0');
            fmt++;
        }

        switch (*fmt) {
        case '%':
            putch('%');
            written++;
            break;
        case 'c':
            putch(va_arg(ap, int));
            written++;
            break;
        case 's':
            written += cprintf_emit_string(va_arg(ap, const char *), width, pad);
            break;
        case 'd':
        case 'i':
            written += cprintf_emit_signed(va_arg(ap, int), width, pad);
            break;
        case 'u':
            written += cprintf_emit_unsigned(va_arg(ap, unsigned int), 10u, false,
                width, pad);
            break;
        case 'x':
            written += cprintf_emit_unsigned(va_arg(ap, unsigned int), 16u, false,
                width, pad);
            break;
        case 'X':
            written += cprintf_emit_unsigned(va_arg(ap, unsigned int), 16u, true,
                width, pad);
            break;
        default:
            putch('%');
            putch(*fmt);
            written += 2;
            break;
        }

        if (*fmt) {
            fmt++;
        }
    }

    return written;
}

int cprintf(const char *fmt, ...) {
    va_list ap;
    int written;

    va_start(ap, fmt);
    written = vcprintf(fmt, ap);
    va_end(ap);
    return written;
}
