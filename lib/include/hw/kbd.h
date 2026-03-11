/*
 * kbd.h
 *
 * Internal keyboard and terminal hardware bindings for Partner.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */

#ifndef LIBPARTNER_HW_KBD_H
#define LIBPARTNER_HW_KBD_H

#include <hw/sio.h>

/* Keyboard/terminal data flows through SIO 1 channel A data register. */
#define KBD_DATA            Z80SIO1_DATA_A
/* Keyboard/terminal status is read from SIO 1 channel A control register. */
#define KBD_STATUS          Z80SIO1_CTRL_A
/* Receive-ready bit used when polling for an incoming key. */
#define KBD_STATUS_RX_READY Z80SIO_RR0_RX_AVAIL
/* Transmit-ready bit used before sending terminal output or BEL. */
#define KBD_STATUS_TX_READY Z80SIO_RR0_TX_EMPTY
/* ASCII BEL sent to the terminal path to request an audible beep. */
#define KBD_CMD_BEEP        0x07

#endif
