        ;; serial.inc
        ;;
        ;; Partner-specific Z80 SIO port map.
        ;;
        ;; NOTES:
        ;;  Partner exposes two SIO devices.
        ;;  SIO 1 is used for keyboard / printer.
        ;;  SIO 2 is used for host / VAX communication.
        ;;  bit 0 selects data vs control.
        ;;  bit 1 selects channel A vs B.
        ;;  port 0xE4 aliases SIO 2 channel A data in the current
        ;;  Partner address decoding.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih

        ;; --- SIO 1: keyboard / printer --------------------------------------
        ;; 0xD8 - Channel A data register
        .equ Z80SIO1_DATA_A,           0xD8
        ;; 0xD9 - Channel A control / status register
        .equ Z80SIO1_CTRL_A,           0xD9
        ;; 0xDA - Channel B data register
        .equ Z80SIO1_DATA_B,           0xDA
        ;; 0xDB - Channel B control / status register
        .equ Z80SIO1_CTRL_B,           0xDB

        ;; --- SIO 2: host / VAX -----------------------------------------------
        ;; 0xE0 - Channel A data register
        .equ Z80SIO2_DATA_A,           0xE0
        ;; 0xE1 - Channel A control / status register
        .equ Z80SIO2_CTRL_A,           0xE1
        ;; 0xE2 - Channel B data register
        .equ Z80SIO2_DATA_B,           0xE2
        ;; 0xE3 - Channel B control / status register
        .equ Z80SIO2_CTRL_B,           0xE3
        ;; 0xE4 - Alias of channel A data in current Partner decoding
        .equ Z80SIO2_DATA_A_ALIAS,     0xE4

        ;; --- RR0 / status bits commonly used for polling ---------------------
        ;; bit 0 - receive character available
        .equ Z80SIO_RR0_RX_AVAIL,      0x01
        ;; bit 2 - transmit buffer empty / ready
        .equ Z80SIO_RR0_TX_EMPTY,      0x04
        ;; bit 3 - data carrier detect
        .equ Z80SIO_RR0_DCD,           0x08
        ;; bit 4 - sync / hunt status
        .equ Z80SIO_RR0_SYNC_HUNT,     0x10
        ;; bit 5 - clear to send
        .equ Z80SIO_RR0_CTS,           0x20
        ;; bit 6 - transmit underrun / end of message
        .equ Z80SIO_RR0_TX_UNDERRUN,   0x40
        ;; bit 7 - break detected / abort
        .equ Z80SIO_RR0_BREAK_ABORT,   0x80
