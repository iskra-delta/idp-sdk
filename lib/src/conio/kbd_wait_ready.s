        ;; kbd_wait_ready.s
        ;;
        ;; Wait for Partner keyboard / terminal TX readiness.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module kbd_wait_ready

        .globl  _kbd_wait_ready

        .include "serial.inc"

        .area   _CODE

        ;; void kbd_wait_ready(void)
        ;; waits until SIO 1 channel A can accept a byte
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_kbd_wait_ready::
.wait:
        in      a,(#Z80SIO1_CTRL_A)
        and     #Z80SIO_RR0_TX_EMPTY
        jr      z,.wait
        ret
