/*
 * console.c
 *
 * Fast console io (conio.h) tests.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 11.08.2021   tstih
 *
 */
#include <stdio.h>
#include <partner.h>

#define ANSI_RESET      "\x1b[0m"
#define ANSI_BOLD       "\x1b[1m"
#define ANSI_REVERSE    "\x1b[7m"
#define ANSI_DIM        "\x1b[2m"

static void print_debug_info(const char *title, const z80_registers_t *regs) {

    printf("\n" ANSI_REVERSE ANSI_BOLD " %s " ANSI_RESET "\n", title);
    printf(ANSI_DIM " main set " ANSI_RESET
           "AF=%04X    BC=%04X    DE=%04X    HL=%04X    IX=%04X    IY=%04X\n",
        regs->af, regs->bc, regs->de, regs->hl, regs->ix, regs->iy);
    printf(ANSI_DIM " state    " ANSI_RESET
           "SP=%04X    PC=%04X    I=%02X      R=%02X\n",
        regs->sp, regs->pc, regs->i, regs->r);
    printf(ANSI_DIM " alt set  " ANSI_RESET
           "AF'=%04X   BC'=%04X   DE'=%04X   HL'=%04X\n",
        regs->af_shadow, regs->bc_shadow, regs->de_shadow, regs->hl_shadow);
}

static const void wait(const char *msg) {
    cputs(msg);
    // while (!kbhit());
}

char line[133];
char text[133];
struct text_info ti;

int main(void) {

unsigned char i;
    unsigned char j;
    char ch;
    unsigned char a;

    /* ----- FILL SCREEN. ------------------------------ */
    for (i = 0; i < 132; i++) {
        line[i] = 'A';
    }
    line[i] = 0;

    for (i = 0; i < 26; i++) {
        gotoxy(0, i);
        cputs(line);
    }
    wait("Press any key.");

    /* ----- HIDE CURSOR AND CLEAR SCREEN--------------- */
    setcursortype(NOCURSOR);
    clrscr();
    setattr(AT_UNDERLINE);
    wait("Press any key.");

    /* ----- SHOW CURSOR AND BLINK --------------------- */
    setcursortype(NORMALCURSOR);
    gotoxy(0, 1);
    setattr(AT_BLINK);
    wait("Press any key.");

    /* ----- GET TEXT INFO ----------------------------- */
    gotoxy(0, 2);
    gettextinfo(&ti);
    setattr(AT_HIGHLIGHT);
    sprintf(text, "Cursor position is x=%d,y=%d", wherex(), wherey());
    cputs(text);
    sprintf(text, " and screen size is x=%d,y=%d", ti.screenwidth, ti.screenheight);
    cputs(text);
    gotoxy(0, 3);
    wait("Press any key.");

    /* ----- CURSOR TO RIGHT BOTTOM CORNER ------------- */
    gotoxy(130, 25);
    cputs("ABC");
    gotoxy(0, 4);
    setattr(AT_REVERSE | AT_HIGHLIGHT);
    wait("Press any key.");

    /* ----- READ CHAR AND ATTRIBUTE ------------------- */
    setcursortype(NOCURSOR);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 132; j++) {
            gotoxy(j, i);
            rdchat(&ch, &a);
            gotoxy(j, 10 + i);
            setattr(a);
            putch(ch);
        }
    }
    gotoxy(0, 17);
    setattr(AT_NORMAL);
    wait("Press any key.");

    return 0;
}
