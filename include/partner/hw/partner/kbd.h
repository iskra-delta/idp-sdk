/*
 * kbd.h
 *
 * Partner keyboard helpers over SIO 1 channel A.
 *
 * NOTES:
 *  - Keyboard input and terminal output use SIO 1 channel A.
 *  - RX ready is RR0 bit 0.
 *  - TX ready is RR0 bit 2.
 *  - Bell output uses ASCII BEL on the keyboard/terminal channel.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#ifndef __PARTNER_KBD_H__
#define __PARTNER_KBD_H__

#include <stdbool.h>
#include <stdint.h>
#include <partner/hw/partner/serial.h>

/* SIO 1 channel A data register used by the keyboard / terminal path. */
#define KBD_DATA            Z80SIO1_DATA_A
/* SIO 1 channel A control / status register. */
#define KBD_STATUS          Z80SIO1_CTRL_A
/* RR0 bit 0 - receive character available. */
#define KBD_STATUS_RX_READY Z80SIO_RR0_RX_AVAIL
/* RR0 bit 2 - transmit buffer empty / ready. */
#define KBD_STATUS_TX_READY Z80SIO_RR0_TX_EMPTY
/* ASCII BEL used to trigger the terminal bell. */
#define KBD_CMD_BEEP        0x07

/* Wait until the keyboard / terminal transmit side is ready. */
void kbd_wait_ready(void);

/* Emit a short bell; long bell sends BEL twice. */
void kbd_beep(bool long_beep);

/* Read a key and collapse ANSI / VT52 escape sequences. */
char kbd_get_key(void);

#endif /* __PARTNER_KBD_H__ */
