        ;; avdc_putchar.s
        ;;
        ;; Partner AVDC single-character write.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_putchar

        .globl  _avdc_putchar
        .globl  _avdc_wait_mem_acc
        .globl  _scn2674_wait_rdy

        .include "avdc.inc"

        .area   _CODE

        ;; avdc_putchar
        ;; writes char and attribute at cursor
        ;; NOTES:
        ;;  writes the character and attribute to the
        ;;  current cursor position without moving it
        ;; inputs: stack args ch, attr
        ;; outputs: none
        ;; affects: af, bc, hl
_avdc_putchar::
        pop     bc
        pop     hl
        push    hl
        push    bc
        call    _avdc_wait_mem_acc
        call    _scn2674_wait_rdy
        ld      a,l
        out     (SCN2674_CHR),a
        ld      a,h
        out     (SCN2674_AT),a
        call    _scn2674_wait_rdy
        call    _scn2674_wait_rdy
        ld      a,#SCN2674_CMD_WAC_NO_MOVE
        out     (SCN2674_CMD),a
        ret
