        ;; kbd_beep.s
        ;;
        ;; Emit Partner keyboard / terminal bell.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module kbd_beep

        .globl  _kbd_beep
        .globl  _kbd_wait_ready

        .include "serial.inc"

        .area   _CODE

        ;; void kbd_beep(bool long_beep)
        ;; emits BEL on SIO 1 channel A
        ;; NOTES:
        ;;  a long beep is approximated by sending BEL twice
        ;; inputs: a=long_beep
        ;; outputs: none
        ;; affects: af, bc
_kbd_beep::
        ld      b,a              ; B = long_beep (save; wait only affects AF)
        call    _kbd_wait_ready
        ld      a,#0x07
        out     (#Z80SIO1_DATA_A),a
        ld      a,b              ; A = long_beep
        or      a
        ret     z

        call    _kbd_wait_ready
        ld      a,#0x07
        out     (#Z80SIO1_DATA_A),a
        ret
