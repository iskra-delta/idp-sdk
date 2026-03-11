/*
 * scn2674.h
 *
 * Internal SCN2674 hardware map for Partner.
 *
 * The controller uses a compact I/O map where the same port can expose
 * different meanings depending on whether it is read or written. The SDK
 * uses this block for text-mode cursor positioning, attribute writes, and
 * fast screen memory access.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */

#ifndef LIBPARTNER_HW_SCN2674_H
#define LIBPARTNER_HW_SCN2674_H

/* Read/write character register used for text data transfers. */
#define SCN2674_CHR                 0x34
/* Read/write attribute register paired with the character register. */
#define SCN2674_AT                  0x35
/* Attribute value: no special rendering. */
#define SCN2674_AT_NONE             0x00
/* Attribute bit: blinking character cell. */
#define SCN2674_AT_BLINK            0x01
/* Attribute bit: underlined character cell. */
#define SCN2674_AT_UNDERLINE        0x02
/* Attribute bit: special/graphic character selection. */
#define SCN2674_AT_SPC_CHR          0x04
/* Attribute bit: protected field. */
#define SCN2674_AT_PROTECT          0x08
/* Attribute bit: highlighted cell / red foreground on write. */
#define SCN2674_AT_HIGHLIGHT        0x10
/* Attribute bit: reverse video / green background on write. */
#define SCN2674_AT_REVERSE          0x20
/* Attribute bit: GP2 / blue background on write. */
#define SCN2674_AT_GP2              0x40
/* Attribute bit: GP1 / red background component on write. */
#define SCN2674_AT_GP1              0x80

/* Write: graphics scroll register. */
#define SCN2674_GR_SCROLL           0x36
/* Read: common input register sharing the same port as graphics scroll. */
#define SCN2674_GR_CMNI             0x36
/* Common input bit: memory access window currently belongs to SCN2674. */
#define SCN2674_GR_CMNI_SCN2674A    0x10
/* Common input bit: graphics pixel input state. */
#define SCN2674_GR_CMNI_PIX         0x80

/* Write: initialization register access port. */
#define SCN2674_INIT                0x38
/* Read: interrupt register sharing the init port. */
#define SCN2674_IR                  0x38
/* Interrupt flag: split-screen 2 event. */
#define SCN2674_IR_SS2              0x01
/* Interrupt flag: ready event. */
#define SCN2674_IR_RDY              0x02
/* Interrupt flag: split-screen 1 event. */
#define SCN2674_IR_SS1              0x04
/* Interrupt flag: line-zero event. */
#define SCN2674_IR_LZ               0x08
/* Interrupt flag: vertical blank event. */
#define SCN2674_IR_VB               0x10

/* Write: command register. */
#define SCN2674_CMD                 0x39
/* Command: master reset the controller. */
#define SCN2674_CMD_RESET           0x00
/* Command: point the init-register sequencer at the low nibble. */
#define SCN2674_CMD_SET_IR          0x10
/* Command: hide the hardware text cursor. */
#define SCN2674_CMD_CURS_OFF        0x30
/* Command: show the hardware text cursor. */
#define SCN2674_CMD_CURS_ON         0x31
/* Command: fill from cursor to pointer. */
#define SCN2674_CMD_WC2P            0xBB
/* Command: write at cursor and advance. */
#define SCN2674_CMD_WAC             0xAB
/* Command: write at cursor without moving it. */
#define SCN2674_CMD_WAC_NO_MOVE     0xAA
/* Command: read at cursor. */
#define SCN2674_CMD_RAC             0xAC
/* Command: read at pointer. */
#define SCN2674_CMD_RDPTR           0xA4

/* Read: status register sharing the command port. */
#define SCN2674_STS                 0x39
/* Status bit: split-screen 2 pending. */
#define SCN2674_STS_SS2             0x01
/* Status bit: ready interrupt pending. */
#define SCN2674_STS_RDYI            0x02
/* Status bit: split-screen 1 pending. */
#define SCN2674_STS_SS1             0x04
/* Status bit: line-zero pending. */
#define SCN2674_STS_LZ              0x08
/* Status bit: vertical blank pending. */
#define SCN2674_STS_VB              0x10
/* Status bit: controller ready for the next access. */
#define SCN2674_STS_RDY             0x20

/* Screen start 1 low byte. */
#define SCN2674_SS1_LO              0x3A
/* Screen start 1 high byte. */
#define SCN2674_SS1_HI              0x3B
/* Cursor address low byte. */
#define SCN2674_CUR_LO              0x3C
/* Cursor address high byte. */
#define SCN2674_CUR_HI              0x3D
/* Screen start 2 low byte. */
#define SCN2674_SS2_LO              0x3E
/* Screen start 2 high byte. */
#define SCN2674_SS2_HI              0x3F

#endif
