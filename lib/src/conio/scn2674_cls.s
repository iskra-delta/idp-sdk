        ;; scn2674_cls.s
        ;;
        ;; Partner SCN2674 clear-screen helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_cls

        .globl  _scn2674_cls
        .globl  _scn2674_cache_rows
        .globl  _scn2674_wait_mem_acc
        .globl  _scn2674_rowptr_raw
        .globl  _scn2674_set_cursor
        .globl  _scn2674_set_pointer
        .globl  _scn2674_wait_rdy

        .include "scn2674.inc"

        .area   _CODE

        ;; scn2674_cls
        ;; clears the text screen through row pointers
        ;; NOTES:
        ;;  iterates all 26 rows, resolves each row start
        ;;  address from the row table, then fills the row
        ;;  with spaces and zero attributes
        ;; inputs: none
        ;; outputs: none
        ;; affects: af, bc, de, hl
_scn2674_cls::
        ld      b,#26
.cls_loop:
        call    _scn2674_wait_mem_acc
        ld      l,b
        dec     l
        call    _scn2674_rowptr_raw
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
        call    _scn2674_rowptr_raw
        call    _scn2674_set_cursor
        call    _scn2674_cache_rows
        ret
