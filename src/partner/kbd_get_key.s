        ;; kbd_get_key.s
        ;;
        ;; Read Partner keyboard key with escape-sequence folding.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module kbd_get_key

        .globl  _kbd_get_key

        .include "serial.inc"

        .area   _CODE

        ;; char kbd_get_key(void)
        ;; reads one key directly from SIO 1 channel A
        ;; NOTES:
        ;;  ESC alone returns 27
        ;;  ESC [ X returns X | 128
        ;;  ESC X returns X | 128
        ;; inputs: none
        ;; outputs: l=key
        ;; affects: af, hl
_kbd_get_key::
        call    .poll
        ld      a,l
        cp      #27
        jr      z,.escape
        ret

.escape:
        call    .poll
        ld      a,l
        or      a
        jr      z,.return_esc
        cp      #91
        jr      z,.ansi
        or      #0x80
        ld      l,a
        ret

.ansi:
        call    .poll
        ld      a,l
        or      #0x80
        ld      l,a
        ret

.return_esc:
        ld      l,#27
        ret

.poll:
        in      a,(#Z80SIO1_CTRL_A)
        and     #Z80SIO_RR0_RX_AVAIL
        jr      z,.none
        in      a,(#Z80SIO1_DATA_A)
        res     7,a
        ld      l,a
        ret

.none:
        ld      l,#0
        ret
