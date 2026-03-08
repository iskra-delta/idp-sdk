        ;; scn2674_set_cursor.s
        ;;
        ;; Raw SCN2674 cursor-address write.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_set_cursor

        .globl  _scn2674_set_cursor
        .globl  _scn2674_wait_rdy

        .include "../partner/avdc.inc"

        .area   _CODE

        ;; scn2674_set_cursor
        ;; writes cursor address from hl
        ;; NOTES:
        ;;  updates the SCN2674 cursor low and high
        ;;  registers after waiting for the device
        ;; inputs: stack arg addr
        ;; outputs: none
        ;; affects: af, hl
_scn2674_set_cursor::
        pop     de
        pop     hl
        push    hl
        push    de
        call    _scn2674_wait_rdy
        ld      a,l
        out     (#SCN2674_CUR_LO),a
        ld      a,h
        out     (#SCN2674_CUR_HI),a
        ret
