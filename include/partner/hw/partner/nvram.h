/*
 * nvram.h
 *
 * Partner system settings stored in MM58167A-backed NVRAM.
 *
 * NOTES:
 *  - These settings are used by the Partner SET UP program.
 *  - They live in MM58167A NVRAM ports 0xA8-0xAF.
 *  - Unknown ports are preserved through the read/modify/write path.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#ifndef __PARTNER_NVRAM_H__
#define __PARTNER_NVRAM_H__

#include <stdbool.h>
#include <stdint.h>

/* 0xA8 - unknown machine / firmware byte */
#define MM58167A_NVRAM_A8             0xA8
/* 0xA9 - software-maintained two-digit year */
#define MM58167A_NVRAM_YEAR           0xA9
/* 0xAA - unknown setup byte */
#define MM58167A_NVRAM_AA             0xAA
/* 0xAB - terminal type and language */
#define MM58167A_NVRAM_TERM_LANG      0xAB
/* 0xAC - screen width */
#define MM58167A_NVRAM_SCREEN_WIDTH   0xAC
/* 0xAD - unknown setup byte */
#define MM58167A_NVRAM_AD             0xAD
/* 0xAE - display behavior flags */
#define MM58167A_NVRAM_DISPLAY        0xAE
/* 0xAF - keyboard flags */
#define MM58167A_NVRAM_KEYBOARD       0xAF

typedef enum {
    NVRAM_TERM_ANSI    = 0x00,
    NVRAM_TERM_PARTNER = 0x10,
    NVRAM_TERM_VT52    = 0x20
} nvram_terminal_type;

typedef enum {
    NVRAM_LANG_US_ASCII = 0x0,
    NVRAM_LANG_UK_ASCII = 0x1,
    NVRAM_LANG_SPANISH  = 0x2,
    NVRAM_LANG_FRENCH   = 0x3,
    NVRAM_LANG_GERMAN   = 0x4,
    NVRAM_LANG_ITALIAN  = 0x5,
    NVRAM_LANG_DANISH   = 0x6,
    NVRAM_LANG_SWEDISH  = 0x7,
    NVRAM_LANG_YUGOSLAV = 0x8
} nvram_language;

typedef enum {
    NVRAM_SCREEN_80  = 0x51,
    NVRAM_SCREEN_132 = 0x85
} nvram_screen_width;

typedef enum {
    NVRAM_LAYOUT_QWERTY = 0,
    NVRAM_LAYOUT_QWERTZ = 1
} nvram_keyboard_layout;

typedef struct nvram_settings_s {
    uint8_t raw_a8;
    uint8_t year;
    uint8_t raw_aa;
    uint8_t raw_ad;
    nvram_terminal_type terminal_type;
    nvram_language language;
    nvram_screen_width screen_width;
    bool reverse_video;
    bool wrap;
    bool auto_newline;
    bool key_click;
    bool autorepeat;
    nvram_keyboard_layout keyboard_layout;
} nvram_settings_t;

/* Read and decode Partner system settings from MM58167A NVRAM. */
extern void nvram_get_settings(nvram_settings_t *settings);

/* Encode and write Partner system settings to MM58167A NVRAM. */
extern void nvram_set_settings(const nvram_settings_t *settings);

#endif /* __PARTNER_NVRAM_H__ */
