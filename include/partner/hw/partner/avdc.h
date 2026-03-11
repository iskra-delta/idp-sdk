/*
 * avdc.h
 *
 * Partner AVDC service declarations.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2022 Tomaz Stih
 *
 * 05.05.2022   tstih
 *
 */
#ifndef __PARTNER_AVDC_H__
#define __PARTNER_AVDC_H__

#include <stdint.h>

/* --- 0x34 - R/W: character register ------------------------------------- */
#define SCN2674_CHR                 0x34

/* --- 0x35 - R/W: attribute register ------------------------------------- */
#define SCN2674_AT                  0x35
/* no attributes */
#define SCN2674_AT_NONE             0x00
/* blink */
#define SCN2674_AT_BLINK            0x01
/* underline */
#define SCN2674_AT_UNDERLINE        0x02
/* special character */
#define SCN2674_AT_SPC_CHR          0x04
/* protect */
#define SCN2674_AT_PROTECT          0x08
/* read: highlight, write: red foreground */
#define SCN2674_AT_HIGHLIGHT        0x10
/* read: reverse, write: green background */
#define SCN2674_AT_REVERSE          0x20
/* read: GP2, write: blue background */
#define SCN2674_AT_GP2              0x40
/* read: GP1, write: red background */
#define SCN2674_AT_GP1              0x80

/* --- 0x36 - W: graphics scroll / R: common input ------------------------ */
/* write: graphics scroll in scan lines */
#define SCN2674_GR_SCROLL           0x36
/* read: common input register */
#define SCN2674_GR_CMNI             0x36
/* SCN2674 access flag */
#define SCN2674_GR_CMNI_SCN2674A    0x10
/* graphics pixel input */
#define SCN2674_GR_CMNI_PIX         0x80

/* --- 0x38 - W: init / R: interrupt register ----------------------------- */
/* write: sequential init register access */
#define SCN2674_INIT                0x38
/* read: interrupt register */
#define SCN2674_IR                  0x38
/* split screen 2 interrupt */
#define SCN2674_IR_SS2              0x01
/* ready interrupt */
#define SCN2674_IR_RDY              0x02
/* split screen 1 interrupt */
#define SCN2674_IR_SS1              0x04
/* line zero interrupt */
#define SCN2674_IR_LZ               0x08
/* vertical blank interrupt */
#define SCN2674_IR_VB               0x10

/* --- 0x39 - W: command / R: status -------------------------------------- */
/* write: command register */
#define SCN2674_CMD                 0x39
/* master reset */
#define SCN2674_CMD_RESET           0x00
/* set init register pointer to lower nibble */
#define SCN2674_CMD_SET_IR          0x10
/* switch off cursor */
#define SCN2674_CMD_CURS_OFF        0x30
/* switch on cursor */
#define SCN2674_CMD_CURS_ON         0x31
/* write from cursor to pointer */
#define SCN2674_CMD_WC2P            0xBB
/* write at cursor */
#define SCN2674_CMD_WAC             0xAB
/* write at cursor without moving cursor */
#define SCN2674_CMD_WAC_NO_MOVE     0xAA
/* read at cursor */
#define SCN2674_CMD_RAC             0xAC
/* read at pointer */
#define SCN2674_CMD_RDPTR           0xA4

/* read: status register */
#define SCN2674_STS                 0x39
/* split screen 2 interrupt */
#define SCN2674_STS_SS2             0x01
/* ready interrupt */
#define SCN2674_STS_RDYI            0x02
/* split screen 1 interrupt */
#define SCN2674_STS_SS1             0x04
/* line zero interrupt */
#define SCN2674_STS_LZ              0x08
/* vertical blank interrupt */
#define SCN2674_STS_VB              0x10
/* ready flag */
#define SCN2674_STS_RDY             0x20

/* --- 0x3A - R/W: screen start 1 lower register -------------------------- */
#define SCN2674_SS1_LO              0x3A
/* --- 0x3B - R/W: screen start 1 upper register -------------------------- */
#define SCN2674_SS1_HI              0x3B

/* --- 0x3C - R/W: cursor address lower register -------------------------- */
#define SCN2674_CUR_LO              0x3C
/* --- 0x3D - R/W: cursor address upper register -------------------------- */
#define SCN2674_CUR_HI              0x3D

/* --- 0x3E - R/W: screen start 2 lower register -------------------------- */
#define SCN2674_SS2_LO              0x3E
/* --- 0x3F - R/W: screen start 2 upper register -------------------------- */
#define SCN2674_SS2_HI              0x3F

/* wait for a safe display memory access window */
extern void avdc_wait_mem_acc(void);

/* get current cursor address */
extern uint16_t avdc_cursor_addr(void);

/* cache current AVDC row addresses */
extern void avdc_cache_rows(void);

/* invalidate cached AVDC row addresses */
extern void avdc_invalidate_row_cache(void);

/* resolve row address for a row index */
extern uint16_t avdc_rowptr(uint8_t row);

/* clear the text screen */
extern void avdc_cls(void);

/* enable text cursor */
extern void avdc_show_cursor(void);

/* disable text cursor */
extern void avdc_hide_cursor(void);

/* move cursor to x,y */
extern void avdc_xy(int x, int y);

/* write char and attribute at cursor */
extern void avdc_putchar(char ch, unsigned char attr);

/* read char and attribute at cursor */
extern void avdc_getchar(char *ch, unsigned char *attr);

#endif /* __PARTNER_AVDC_H__ */
