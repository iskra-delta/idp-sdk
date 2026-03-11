        ;; scn2674_set_pointer.s
        ;;
        ;; Raw SCN2674 pointer-register write.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_set_pointer

        .globl  _scn2674_set_pointer
        .globl  _scn2674_wait_rdy

        .include "scn2674.inc"

        .area   _CODE

        ;; scn2674_set_pointer
        ;; writes pointer address from hl
        ;; NOTES:
        ;;  programs the SCN2674 pointer registers by
        ;;  first selecting the initialization register
        ;;  pair and then writing low/high bytes
        ;; inputs: hl=addr
        ;; outputs: none
        ;; affects: af
_scn2674_set_pointer::
        call    _scn2674_wait_rdy
        ld      a,#0x1A
        out     (#SCN2674_CMD), a
        ld      a,l
        out     (#SCN2674_INIT),a
        ld      a,h
        out     (#SCN2674_INIT),a
        ret
