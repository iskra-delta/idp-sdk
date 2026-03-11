/*
 * conio.h
 *
 * Public conio declarations for libpartner.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 * 03.08.2021   tstih
 *
 */
#ifndef __CONIO_H__
#define __CONIO_H__

#include <stdbool.h>
#include <stdint.h>
#include <sys/bdos.h>

#define AT_NORMAL       0x00
#define AT_BLINK        0x01
#define AT_UNDERLINE    0x02
#define AT_HIGHLIGHT    0x10
#define AT_REVERSE      0x20

struct text_info {
    unsigned char attr;         /* Current attribute. */
    unsigned char screenheight; /* text screen's height */
    unsigned char screenwidth;  /* text screen's width */
    unsigned char curx;         /* x-coordinate */
    unsigned char cury;         /* y-coordinate */
}; 

/* Check for keypress using the currently selected backend. */
extern int kbhit(void);

/* Select whether kbhit() uses BDOS or raw keyboard polling. */
extern void kbhit_set_bdos(bool use_bdos);

/* move cursor to x,y */
extern void gotoxy(int x, int y);

/* clear screen and move cursor to 0,0 */
extern void clrscr(void);

/* Set raw attribute */
void setattr(unsigned char attr);

/* get screen dimensions */
extern void gettextinfo(struct text_info *r);

/* fast put character */
extern int putch(int c);

/* read char and attr at cursor */
extern void rdchat(char *c, unsigned char *attr);

/* fast put string */
extern int cputs(const char *str);

/* formatted console output without stdio */
extern int cprintf(const char *fmt, ...);

/* current x */
extern int wherex(void);

/* current y */
extern int wherey(void);

/* set cursor type */
#define NOCURSOR        0
#define NORMALCURSOR    1
extern void setcursortype(int cur_t);

/* Trigger a short or long keyboard beep. */
extern void kbd_beep(bool long_beep);

/* Poll one raw key value from the keyboard interface.
 * SIO 1 channel A must already be configured for polling before use.
 */
extern char kbd_poll_key(void);

/* Wait until the display controller memory access is available. */
extern void scn2674_wait_mem_acc(void);

/* Read the current display controller cursor address. */
extern uint16_t scn2674_cursor_addr(void);

/* Refresh the cached row base addresses. */
extern void scn2674_cache_rows(void);

/* Mark cached row base addresses as invalid. */
extern void scn2674_invalidate_row_cache(void);

/* Return the display memory address for the requested row. */
extern uint16_t scn2674_rowptr(uint8_t row);

/* Clear the display through the controller fast path. */
extern void scn2674_cls(void);

/* Show the hardware cursor. */
extern void scn2674_show_cursor(void);

/* Hide the hardware cursor. */
extern void scn2674_hide_cursor(void);

/* Move the hardware cursor to the requested coordinates. */
extern void scn2674_xy(int x, int y);

/* Write a character and attribute through the display controller. */
extern void scn2674_putchar(char ch, unsigned char attr);

/* Read a character and attribute through the display controller. */
extern void scn2674_getchar(char *ch, unsigned char *attr);

#endif /* __CONIO_H__ */
