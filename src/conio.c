/*
 * conio.c
 *
 * Parts of conio.h, implemented by libpartner.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 * 03.08.2021   tstih
 *
 */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <partner/conio.h>
#include <partner/hw/partner/avdc.h>
#include <partner/hw/partner/kbd.h>

/* Current text_info */
static struct text_info _ti = {
    0x00,   /* attr */
    26,     /* screenheight */
    0x00,   /* screenwidth */
    0xff,   /* curx */
    0xff    /* cury */
};


__sfr __at 0xac _SETUP_WIDTH;

/* Fill caller-supplied text_info with current console state. */
void gettextinfo(struct text_info *r) {
    r->curx=wherex();
    r->cury=wherey();
    r->attr=_ti.attr;
    r->screenheight=_ti.screenheight;
    /* Read directly from hardware. */
    _ti.screenwidth=_SETUP_WIDTH - 1;
    r->screenwidth=_ti.screenwidth;
}

/* Return the pending key code, or 0 when no key is available. */
int kbhit(void) {
    return (unsigned char)kbd_get_key();
}


/* Return current cursor column. */
int wherex(void) {
    if (_ti.curx==0xff) { /* Current col undefined. */
        uint8_t y=wherey();
        if (y!=0xff) /* Only if we have a meaningful y! */
            _ti.curx=avdc_cursor_addr() - avdc_rowptr(y);
    }
    return _ti.curx;
}


/* Return current cursor row. */
int wherey(void) {
    if (_ti.cury==0xff) { /* Current row undefined? */
        uint16_t curaddr=avdc_cursor_addr();
        for(unsigned char row=0;row<26;row++) {
            uint16_t rowaddr=avdc_rowptr(row);
            if (curaddr>=rowaddr && curaddr<rowaddr+132) { 
                _ti.cury=row;
                return row;
            }
        }
    }
    /* If we are here it's in gods hands. */
    return _ti.cury;
}


/* Show or hide the cursor. */
void setcursortype(int cur_t) {
    if (cur_t==NOCURSOR)
        avdc_hide_cursor();
    else
        avdc_show_cursor();
}


/* Set current text attribute. */
void setattr(unsigned char attr) {
    _ti.attr=attr;
}

/* Read character and attribute at the current cursor position. */
void rdchat(char *c, unsigned char *attr) {
    avdc_getchar(c,attr);
}


/* Clear screen and reset cached cursor and attribute state. */
void clrscr(void) {
    avdc_cls();
    _ti.attr=0;
    _ti.screenwidth=_SETUP_WIDTH - 1;
    _ti.curx=0; _ti.cury=0;
}


/* Move cursor to x,y if the coordinates are valid. */
void gotoxy(int x, int y) {
    /* Make sure the coordinate is valid. */
    if (x>=0 && x<_SETUP_WIDTH-1 && y>=0 && y<_ti.screenheight) {
        avdc_xy(x,y);
        /* Update current x and y. */
        _ti.curx=x;
        _ti.cury=y;
    } else  
        _ti.curx=_ti.cury=0xff; /* Invalidate. */
}


/* Write one character at the current cursor position. */
int putch(int c) {
    char ch=c;
    if (wherex()<_SETUP_WIDTH-2) {
        _ti.curx=wherex()+1;
        avdc_burst(&ch,_ti.attr,1);
    }
    else if ((wherex()==_SETUP_WIDTH-2))
        avdc_putchar(ch,_ti.attr);
    return c;
}


/* Write a string clipped to the current line width. */
int cputs(const char *s) {
    /* first clip the string. */
    int len=strlen(s);
    if (!len) return 0;
    if (wherex()+len>=_SETUP_WIDTH-1)
        len=(_SETUP_WIDTH-1)-wherex();
    if (len>1) {
        avdc_burst(s,_ti.attr,len-1);
        _ti.curx=wherex()+len-1;
    }
    putch(s[len-1]);
    return len;
}
