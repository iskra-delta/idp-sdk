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
        .globl  _scn2674_wait_mem_acc

        .include "scn2674.inc"

        .area   _CODE

        ;; scn2674_get_cursor
        ;; reads cursor address into de
        ;; NOTES:
        ;;  reads the SCN2674 cursor low and high
        ;;  registers during a valid display-memory
        ;;  access window and after the device is ready
        ;; inputs: none
        ;; outputs: de=cursor address
        ;; affects: af, de
_scn2674_get_cursor::
        call    _scn2674_wait_mem_acc
        call    _scn2674_wait_rdy
        in      a,(#SCN2674_CUR_LO)
        ld      e,a
        in      a,(#SCN2674_CUR_HI)
        ld      d,a
        ret
