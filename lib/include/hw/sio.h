/*
 * sio.h
 *
 * Internal Z80 SIO hardware map for Partner.
 *
 * Z80 SIO layout on Partner:
 * - SIO 1 serves the keyboard/terminal path and the printer path.
 * - SIO 2 serves host/VAX communications.
 * - Even ports are data registers, odd ports are control/status registers.
 * - Channel A is the lower pair in each block, channel B the upper pair.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */

#ifndef LIBPARTNER_HW_SIO_H
#define LIBPARTNER_HW_SIO_H

/* SIO 1 channel A data register: keyboard receive / terminal transmit data. */
#define Z80SIO1_DATA_A          0xD8
/* SIO 1 channel A control and RR0 status register. */
#define Z80SIO1_CTRL_A          0xD9
/* SIO 1 channel B data register: printer-side data path. */
#define Z80SIO1_DATA_B          0xDA
/* SIO 1 channel B control and RR0 status register. */
#define Z80SIO1_CTRL_B          0xDB

/* SIO 2 channel A data register: host/VAX data path. */
#define Z80SIO2_DATA_A          0xE0
/* SIO 2 channel A control and RR0 status register. */
#define Z80SIO2_CTRL_A          0xE1
/* SIO 2 channel B data register: modem/secondary host path. */
#define Z80SIO2_DATA_B          0xE2
/* SIO 2 channel B control and RR0 status register. */
#define Z80SIO2_CTRL_B          0xE3
/* Emulator-visible alias that decodes like SIO 2 channel A data. */
#define Z80SIO2_DATA_A_ALIAS    0xE4

/* RR0 bit 0: one or more received characters are waiting in the FIFO. */
#define Z80SIO_RR0_RX_AVAIL     0x01
/* RR0 bit 2: transmitter buffer is empty and can accept the next byte. */
#define Z80SIO_RR0_TX_EMPTY     0x04
/* RR0 bit 3: carrier detect is asserted. */
#define Z80SIO_RR0_DCD          0x08
/* RR0 bit 4: sync/hunt state, relevant in synchronous modes. */
#define Z80SIO_RR0_SYNC_HUNT    0x10
/* RR0 bit 5: clear-to-send input is asserted. */
#define Z80SIO_RR0_CTS          0x20
/* RR0 bit 6: transmit underrun / end-of-message condition. */
#define Z80SIO_RR0_TX_UNDERRUN  0x40
/* RR0 bit 7: break received or abort condition detected. */
#define Z80SIO_RR0_BREAK_ABORT  0x80

#endif
