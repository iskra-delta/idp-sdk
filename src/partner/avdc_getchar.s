        ;; avdc_getchar.s
        ;;
        ;; Partner AVDC single-character read.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_getchar

        .globl  _avdc_getchar
        .globl  _avdc_wait_mem_acc
        .globl  _scn2674_wait_rdy

        .include "avdc.inc"

        .area   _CODE

        ;; avdc_getchar
        ;; reads char and attribute at cursor
        ;; NOTES:
        ;;  reads the character and attribute from the
        ;;  current cursor position without moving it
        ;; inputs: hl=ch, de=attr
        ;; outputs: *ch=character, *attr=attribute
        ;; affects: af, bc, hl
_avdc_getchar::
        call    _avdc_wait_mem_acc
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
