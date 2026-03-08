/*
 * sysinfo.c
 *
 * Display Partner SET UP values decoded from MM58167A NVRAM.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#include <stdio.h>

#include <partner.h>

static char text[96];

static const char *terminal_name(nvram_terminal_type type) {
    switch (type) {
    case NVRAM_TERM_ANSI:
        return "ANSI";
    case NVRAM_TERM_PARTNER:
        return "Partner";
    case NVRAM_TERM_VT52:
        return "VT52";
    default:
        return "Unknown";
    }
}

static const char *language_name(nvram_language lang) {
    switch (lang) {
    case NVRAM_LANG_US_ASCII:
        return "US ASCII";
    case NVRAM_LANG_UK_ASCII:
        return "UK ASCII";
    case NVRAM_LANG_SPANISH:
        return "Spanish";
    case NVRAM_LANG_FRENCH:
        return "French";
    case NVRAM_LANG_GERMAN:
        return "German";
    case NVRAM_LANG_ITALIAN:
        return "Italian";
    case NVRAM_LANG_DANISH:
        return "Danish";
    case NVRAM_LANG_SWEDISH:
        return "Swedish";
    case NVRAM_LANG_YUGOSLAV:
        return "Yugoslav";
    default:
        return "Unknown";
    }
}

static const char *screen_name(nvram_screen_width width) {
    switch (width) {
    case NVRAM_SCREEN_80:
        return "80 columns";
    case NVRAM_SCREEN_132:
        return "132 columns";
    default:
        return "Unknown";
    }
}

static const char *layout_name(nvram_keyboard_layout layout) {
    return layout == NVRAM_LAYOUT_QWERTZ ? "QWERTZ" : "QWERTY";
}

static const char *yesno(int enabled) {
    return enabled ? "yes" : "no";
}

void main(void) {
    nvram_settings_t settings;

    clrscr();
    nvram_get_settings(&settings);

    cputs("Partner SET UP values from NVRAM\r\n");
    cputs("--------------------------------\r\n");

    sprintf(text, "Terminal     : %s\r\n", terminal_name(settings.terminal_type));
    cputs(text);

    sprintf(text, "Language     : %s\r\n", language_name(settings.language));
    cputs(text);

    sprintf(text, "Screen width : %s\r\n", screen_name(settings.screen_width));
    cputs(text);

    sprintf(text, "Reverse video: %s\r\n", yesno(settings.reverse_video));
    cputs(text);

    sprintf(text, "Wrap         : %s\r\n", yesno(settings.wrap));
    cputs(text);

    sprintf(text, "Auto newline : %s\r\n", yesno(settings.auto_newline));
    cputs(text);

    sprintf(text, "Key click    : %s\r\n", yesno(settings.key_click));
    cputs(text);

    sprintf(text, "Autorepeat   : %s\r\n", yesno(settings.autorepeat));
    cputs(text);

    sprintf(text, "Keyboard     : %s\r\n", layout_name(settings.keyboard_layout));
    cputs(text);

    sprintf(text, "Year         : %02u\r\n", settings.year);
    cputs(text);

    sprintf(text, "Raw A8       : %02X\r\n", settings.raw_a8);
    cputs(text);

    sprintf(text, "Raw AA       : %02X\r\n", settings.raw_aa);
    cputs(text);

    sprintf(text, "Raw AD       : %02X\r\n", settings.raw_ad);
    cputs(text);

    cputs("\r\nPress any key.");
    while (!kbhit()) {
    }
}
