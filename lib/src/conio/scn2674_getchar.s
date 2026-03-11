        ;; scn2674_getchar.s
        ;;
        ;; Partner SCN2674 single-character read.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_getchar

        .globl  _scn2674_getchar
        .globl  _scn2674_wait_mem_acc
        .globl  _scn2674_wait_rdy

        .include "scn2674.inc"

        .area   _CODE

        ;; scn2674_getchar
        ;; reads char and attribute at cursor
        ;; NOTES:
        ;;  reads the character and attribute from the
        ;;  current cursor position without moving it
        ;; inputs: hl=ch, de=attr
        ;; outputs: *ch=character, *attr=attribute
        ;; affects: af, bc, hl
_scn2674_getchar::
        call    _scn2674_wait_mem_acc
        call    _scn2674_wait_rdy
        ld      a,#SCN2674_CMD_RAC
        out     (SCN2674_CMD),a
        call    _scn2674_wait_rdy
        in      a,(SCN2674_CHR)
        ld      (hl),a
        ex      de,hl
        in      a,(SCN2674_AT)
        ld      (hl),a
        ret
