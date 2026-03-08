/*
 * nvram.c
 *
 * Partner system settings stored in MM58167A-backed NVRAM.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#include <partner/port.h>
#include <partner/hw/partner/nvram.h>

/* Decode the 0xAB terminal/language byte into structured fields. */
static void nvram_decode_term_lang(nvram_settings_t *settings, uint8_t value) {
    settings->terminal_type = (nvram_terminal_type)(value & 0xF0);
    settings->language = (nvram_language)(value & 0x0F);
}

/* Encode terminal/language fields into the 0xAB NVRAM byte. */
static uint8_t nvram_encode_term_lang(const nvram_settings_t *settings) {
    return (uint8_t)((uint8_t)settings->terminal_type | (uint8_t)settings->language);
}

/* Decode the 0xAE display-options byte. */
static void nvram_decode_display(nvram_settings_t *settings, uint8_t value) {
    settings->reverse_video = (value & 0x01) != 0;
    settings->wrap = (value & 0x02) != 0;
    settings->auto_newline = (value & 0x04) != 0;
}

/* Encode display flags into the 0xAE NVRAM byte. */
static uint8_t nvram_encode_display(const nvram_settings_t *settings) {
    uint8_t value = 0;

    if (settings->reverse_video) {
        value |= 0x01;
    }
    if (settings->wrap) {
        value |= 0x02;
    }
    if (settings->auto_newline) {
        value |= 0x04;
    }
    return value;
}

/* Decode the 0xAF keyboard-options byte. */
static void nvram_decode_keyboard(nvram_settings_t *settings, uint8_t value) {
    settings->key_click = (value & 0x08) == 0;
    settings->autorepeat = (value & 0x20) == 0;
    settings->keyboard_layout = (value & 0x80) != 0
        ? NVRAM_LAYOUT_QWERTZ
        : NVRAM_LAYOUT_QWERTY;
}

/* Encode keyboard fields into the 0xAF NVRAM byte. */
static uint8_t nvram_encode_keyboard(const nvram_settings_t *settings) {
    uint8_t value = 0x28;

    if (!settings->key_click) {
        value |= 0x08;
    } else {
        value &= (uint8_t)~0x08;
    }

    if (!settings->autorepeat) {
        value |= 0x20;
    } else {
        value &= (uint8_t)~0x20;
    }

    if (settings->keyboard_layout == NVRAM_LAYOUT_QWERTZ) {
        value |= 0x80;
    } else {
        value &= (uint8_t)~0x80;
    }

    return value;
}

/* Read and decode Partner system settings from MM58167A NVRAM. */
void nvram_get_settings(nvram_settings_t *settings) {
    settings->raw_a8 = port_in(MM58167A_NVRAM_A8);
    settings->year = port_in(MM58167A_NVRAM_YEAR);
    settings->raw_aa = port_in(MM58167A_NVRAM_AA);
    nvram_decode_term_lang(settings, port_in(MM58167A_NVRAM_TERM_LANG));
    settings->screen_width = (nvram_screen_width)port_in(MM58167A_NVRAM_SCREEN_WIDTH);
    settings->raw_ad = port_in(MM58167A_NVRAM_AD);
    nvram_decode_display(settings, port_in(MM58167A_NVRAM_DISPLAY));
    nvram_decode_keyboard(settings, port_in(MM58167A_NVRAM_KEYBOARD));
}

/* Encode and write Partner system settings to MM58167A NVRAM. */
void nvram_set_settings(const nvram_settings_t *settings) {
    port_out(MM58167A_NVRAM_A8, settings->raw_a8);
    port_out(MM58167A_NVRAM_YEAR, settings->year);
    port_out(MM58167A_NVRAM_AA, settings->raw_aa);
    port_out(MM58167A_NVRAM_TERM_LANG, nvram_encode_term_lang(settings));
    port_out(MM58167A_NVRAM_SCREEN_WIDTH, (uint8_t)settings->screen_width);
    port_out(MM58167A_NVRAM_AD, settings->raw_ad);
    port_out(MM58167A_NVRAM_DISPLAY, nvram_encode_display(settings));
    port_out(MM58167A_NVRAM_KEYBOARD, nvram_encode_keyboard(settings));
}
