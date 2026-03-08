        ;; rtc_set.s
        ;;
        ;; Partner RTC write helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module rtc_set

        .globl  _rtc_set
        .globl  _rtc_reset
        .globl  _bin2bcd

        .include "rtc.inc"

        .area   _CODE

        ;; rtc_set
        ;; write binary date/time to rtc
        ;; NOTES:
        ;;  resets the running clock and then writes the
        ;;  fields in descending significance order
        ;; inputs: hl=const rtc_time_t *
        ;; outputs: none
        ;; affects: af, bc, de, hl
_rtc_set::
        push    hl
        call    _rtc_reset
        pop     de

        ld      c,e
        ld      b,d
        ld      hl,#7
        add     hl,bc
        ld      a,(hl)
        push    de
        call    _bin2bcd
        pop     de
        out     (MM58167A_YEAR),a

        ld      c,e
        ld      b,d
        ld      hl,#6
        add     hl,bc
        ld      a,(hl)
        push    de
        call    _bin2bcd
        pop     de
        out     (MM58167A_MONTH),a

        ld      c,e
        ld      b,d
        ld      hl,#5
        add     hl,bc
        ld      a,(hl)
        push    de
        call    _bin2bcd
        pop     de
        out     (MM58167A_MDAY),a

        ld      c,e
        ld      b,d
        ld      hl,#4
        add     hl,bc
        ld      a,(hl)
        push    de
        call    _bin2bcd
        pop     de
        out     (MM58167A_WDAY),a

        ld      l,e
        ld      h,d
        inc     hl
        inc     hl
        inc     hl
        ld      a,(hl)
        push    de
        call    _bin2bcd
        pop     de
        out     (MM58167A_HOUR),a

        ld      l,e
        ld      h,d
        inc     hl
        inc     hl
        ld      a,(hl)
        push    de
        call    _bin2bcd
        pop     de
        out     (MM58167A_MINUTE),a

        inc     de
        ld      a,(de)
        call    _bin2bcd
        out     (MM58167A_SECOND),a
        ret
