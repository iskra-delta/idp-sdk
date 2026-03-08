        ;; scn2674_get_cursor.s
        ;;
        ;; Raw SCN2674 cursor-address read.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_get_cursor

        .globl  _scn2674_get_cursor
        .globl  _scn2674_wait_rdy

        .include "../partner/avdc.inc"

        .area   _CODE

        ;; scn2674_get_cursor
        ;; reads cursor address into hl
        ;; NOTES:
        ;;  reads the SCN2674 cursor low and high
        ;;  registers after waiting for the device
        ;; inputs: none
        ;; outputs: hl=cursor address
        ;; affects: af, hl
_scn2674_get_cursor::
        call    _scn2674_wait_rdy
        in      a,(#SCN2674_CUR_LO)
        ld      l,a
        in      a,(#SCN2674_CUR_HI)
        ld      h,a
        ret
