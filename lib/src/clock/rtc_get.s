        ;; rtc_get.s
        ;;
        ;; Partner RTC read helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module rtc_get

        .globl  _rtc_get
        .globl  _bcd2bin

        .include "rtc.inc"

        .area   _CODE

        ;; rtc_get
        ;; read binary date/time from rtc
        ;; NOTES:
        ;;  retries across second rollover so the caller gets
        ;;  a stable snapshot of the RTC state
        ;; inputs: de=rtc_time_t *
        ;; outputs: none
        ;; affects: af, bc, de, hl, ix
_rtc_get::
        push    ix
        ld      ix,#0
        add     ix,sp
        dec     sp
        ex      de,hl
.read_loop:
        push    de
        push    de
        in      a,(MM58167A_HUNDR_S)
        call    _bcd2bin
        pop     de
        pop     bc
        ld      (bc),a

        push    de
        in      a,(MM58167A_SECOND)
        call    _bcd2bin
        ld      -1(ix),a
        pop     de

        ld      c,e
        ld      b,d
        inc     bc
        ld      a,-1(ix)
        ld      (bc),a

        ld      c,e
        ld      b,d
        inc     bc
        inc     bc
        push    bc
        push    de
        in      a,(MM58167A_MINUTE)
        call    _bcd2bin
        pop     de
        pop     bc
        ld      (bc),a

        ld      c,e
        ld      b,d
        inc     bc
        inc     bc
        inc     bc
        push    bc
        push    de
        in      a,(MM58167A_HOUR)
        call    _bcd2bin
        pop     de
        pop     bc
        ld      (bc),a

        ld      hl,#0x0004
        add     hl,de
        push    hl
        push    de
        in      a,(MM58167A_WDAY)
        call    _bcd2bin
        pop     de
        pop     hl
        ld      (hl),a

        ld      hl,#0x0005
        add     hl,de
        push    hl
        push    de
        in      a,(MM58167A_MDAY)
        call    _bcd2bin
        pop     de
        pop     hl
        ld      (hl),a

        ld      hl,#0x0006
        add     hl,de
        push    hl
        push    de
        in      a,(MM58167A_MONTH)
        call    _bcd2bin
        pop     de
        pop     hl
        ld      (hl),a

        ld      hl,#0x0007
        add     hl,de
        push    hl
        push    de
        in      a,(MM58167A_YEAR)
        call    _bcd2bin
        pop     de
        pop     hl
        ld      (hl),a

        push    de
        in      a,(MM58167A_SECOND)
        call    _bcd2bin
        pop     de
        sub     a,-1(ix)
        jr      nz,.read_loop

        inc     sp
        pop     ix
        ret
