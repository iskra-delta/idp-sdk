        ;; kbd_poll_key.s
        ;;
        ;; Poll Partner keyboard key with escape-sequence folding.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module kbd_poll_key

        .globl  _kbd_poll_key

        .include "serial.inc"

        .area   _CODE

        ;; char kbd_poll_key(void)
        ;; polls one key directly from SIO 1 channel A
        ;; NOTES:
        ;;  raw polling API: SIO 1 channel A must already be
        ;;  configured for polling before this is used
        ;;  ESC alone returns 27
        ;;  ESC [ X returns X | 128
        ;;  ESC X returns X | 128
        ;; inputs: none
        ;; outputs: a=key
        ;; affects: af
_kbd_poll_key::
        call    .poll
        cp      #27
        jr      z,.escape
        ret

.escape:
        call    .poll
        or      a
        jr      z,.return_esc
        cp      #91
        jr      z,.ansi
        or      #0x80
        ret

.ansi:
        call    .poll
        or      #0x80
        ret

.return_esc:
        ld      a,#27
        ret

.poll:
        di
        in      a,(#Z80SIO1_CTRL_A)
        and     #Z80SIO_RR0_RX_AVAIL
        jr      z,.none
        in      a,(#Z80SIO1_DATA_A)
        res     7,a
        ei
        ret

.none:
        ei
        xor     a
        ret
