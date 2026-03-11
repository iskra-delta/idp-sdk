        ;; avdc_cls.s
        ;;
        ;; Partner AVDC clear-screen helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_cls

        .globl  _avdc_cls
        .globl  _avdc_cache_rows
        .globl  _avdc_wait_mem_acc
        .globl  _avdc_rowptr_raw
        .globl  _scn2674_set_cursor
        .globl  _scn2674_set_pointer
        .globl  _scn2674_wait_rdy

        .include "avdc.inc"

        .area   _CODE

        ;; avdc_cls
        ;; clears the text screen through row pointers
        ;; NOTES:
        ;;  iterates all 26 rows, resolves each row start
        ;;  address from the row table, then fills the row
        ;;  with spaces and zero attributes
        ;; inputs: none
        ;; outputs: none
        ;; affects: af, bc, de, hl
_avdc_cls::
        ld      b,#26
.cls_loop:
        call    _avdc_wait_mem_acc
        ld      l,b
        dec     l
        call    _avdc_rowptr_raw
        call    _scn2674_set_cursor
        ld      de,#131
        add     hl,de
        call    _scn2674_set_pointer
        call    _scn2674_wait_rdy
        ld      a,#32
        out     (#SCN2674_CHR),a
        xor     a
        out     (#SCN2674_AT),a
        ld      a,#SCN2674_CMD_WC2P
        out     (#SCN2674_CMD),a
        djnz    .cls_loop
        ld      l,#0
        call    _avdc_rowptr_raw
        call    _scn2674_set_cursor
        call    _avdc_cache_rows
        ret
