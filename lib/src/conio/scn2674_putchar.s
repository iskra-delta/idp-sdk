        ;; scn2674_putchar.s
        ;;
        ;; Partner SCN2674 single-character write.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_putchar

        .globl  _scn2674_putchar
        .globl  _scn2674_wait_mem_acc
        .globl  _scn2674_wait_rdy

        .include "scn2674.inc"

        .area   _CODE

        ;; scn2674_putchar
        ;; writes char and attribute at cursor
        ;; NOTES:
        ;;  writes the character and attribute to the
        ;;  current cursor position and lets the controller advance
        ;; inputs: a=ch, l=attr
        ;; outputs: none
        ;; affects: af, bc, hl
_scn2674_putchar::
        ld      b,a              ; B = ch (save; wait calls only affect AF)
        call    _scn2674_wait_mem_acc
        call    _scn2674_wait_rdy
        ld      a,b              ; A = ch
        out     (SCN2674_CHR),a
        ld      a,l              ; A = attr (L preserved across calls)
        out     (SCN2674_AT),a
        call    _scn2674_wait_rdy
        call    _scn2674_wait_rdy
        ld      a,#SCN2674_CMD_WAC
        out     (SCN2674_CMD),a
        ret
