/*
 * mouse.c
 *
 * Text-mode serial mouse demo.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#include <stdint.h>
#include <stdio.h>

#include <partner/conio.h>
#include <partner/mouse.h>

#define SCREEN_WIDTH   132
#define SCREEN_HEIGHT  26
#define STATUS_ROW     0
#define FIELD_ROW      2
#define POINTER_CH     '+'

static void draw_status(const mouse_t *mouse) {
    char text[64];

    gotoxy(0, STATUS_ROW);
    setattr(AT_NORMAL);
    sprintf(text, "x=%3d y=%2d buttons=%u   ", mouse->x, mouse->y, mouse->buttons);
    cputs(text);
}

static void draw_pointer(uint8_t x, uint8_t y, char ch) {
    gotoxy(x, y);
    setattr(AT_REVERSE | AT_HIGHLIGHT);
    putch(ch);
}

void main(void) {
    mouse_t *mouse;
    uint8_t x;
    uint8_t y;
    uint8_t old_x;
    uint8_t old_y;

    clrscr();
    setcursortype(NOCURSOR);
    gotoxy(0, 0);
    cputs("Partner mouse demo. Press any key to quit.");

    mouse = mouse_init(MOUSE_GENIUS_C7);
    if (!mouse) {
        gotoxy(0, 1);
        cputs("mouse_init failed.");
        return;
    }

    mouse->x = SCREEN_WIDTH / 2;
    mouse->y = SCREEN_HEIGHT / 2;
    old_x = (uint8_t)mouse->x;
    old_y = (uint8_t)mouse->y;

    draw_status(mouse);
    draw_pointer(old_x, old_y, POINTER_CH);

    while (!kbhit()) {
        mouse_poll(mouse);

        if (mouse->x < 0) {
            mouse->x = 0;
        } else if (mouse->x >= SCREEN_WIDTH) {
            mouse->x = SCREEN_WIDTH - 1;
        }

        if (mouse->y < FIELD_ROW) {
            mouse->y = FIELD_ROW;
        } else if (mouse->y >= SCREEN_HEIGHT) {
            mouse->y = SCREEN_HEIGHT - 1;
        }

        x = (uint8_t)mouse->x;
        y = (uint8_t)mouse->y;

        if (x != old_x || y != old_y) {
            draw_pointer(old_x, old_y, ' ');
            draw_pointer(x, y, POINTER_CH);
            old_x = x;
            old_y = y;
        }

        draw_status(mouse);
    }

    mouse_done(mouse);
    setattr(AT_NORMAL);
    setcursortype(NORMALCURSOR);
    gotoxy(0, SCREEN_HEIGHT - 1);
    cputs("Done.");
}
