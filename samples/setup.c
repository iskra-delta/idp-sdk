/*
 * setup.c
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

nvram_settings_t settings;

static char *terminal_name(nvram_terminal_type type) {
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

static char *language_name(nvram_language lang) {
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

static char *screen_name(nvram_screen_width width) {
    switch (width) {
    case NVRAM_SCREEN_80:
        return "80 columns";
    case NVRAM_SCREEN_132:
        return "132 columns";
    default:
        return "Unknown";
    }
}

static char *layout_name(nvram_keyboard_layout layout) {
    return layout == NVRAM_LAYOUT_QWERTZ ? "QWERTZ" : "QWERTY";
}

static char *yesno(int enabled) {
    return enabled ? "yes" : "no";
}

int main(void) {
    nvram_get_settings(&settings);

    printf("Partner SET UP values from NVRAM\n");
    printf("--------------------------------\n");
    printf("Terminal     : %s\n", terminal_name(settings.terminal_type));
    printf("Language     : %s\n", language_name(settings.language));
    printf("Screen width : %s\n", screen_name(settings.screen_width));
    printf("Reverse video: %s\n", yesno(settings.reverse_video));
    printf("Wrap         : %s\n", yesno(settings.wrap));
    printf("Auto newline : %s\n", yesno(settings.auto_newline));
    printf("Key click    : %s\n", yesno(settings.key_click));
    printf("Autorepeat   : %s\n", yesno(settings.autorepeat));
    printf("Keyboard     : %s\n", layout_name(settings.keyboard_layout));
    printf("Year         : %02u\n", settings.year);
    printf("Raw A8       : %02X\n", settings.raw_a8);
    printf("Raw AA       : %02X\n", settings.raw_aa);
    printf("Raw AD       : %02X\n", settings.raw_ad);
    printf("\nPress any key.");

    return 0;
}
