        ;; avdc_rowptr_raw.s
        ;;
        ;; Partner AVDC raw row-table read.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_rowptr_raw

        .globl  _avdc_rowptr_raw
        .globl  _scn2674_set_pointer
        .globl  _scn2674_wait_rdy

        .include "avdc.inc"

        .area   _CODE

        ;; avdc_read_at_pointer
        ;; reads character and attribute at pointer
        ;; NOTES:
        ;;  uses the current pointer address and the SCN2674
        ;;  read command to fetch char and attribute bytes
        ;; inputs: hl=memory address
        ;; outputs: e=char, d=attribute
        ;; affects: af, de, hl
.avdc_read_at_pointer:
        push    hl
        call    _scn2674_set_pointer
        ld      a,#SCN2674_CMD_RDPTR
        out     (SCN2674_CMD),a
        call    _scn2674_wait_rdy
        in      a,(SCN2674_CHR)
        ld      e,a
        in      a,(SCN2674_AT)
        ld      d,a
        pop     hl
        ret

        ;; avdc_rowptr_raw
        ;; returns row address
        ;; NOTES:
        ;;  on Partner a row table mode is used to access
        ;;  rows. row table spans from addr 0 to addr 52.
        ;;  this is enough to store pointers for 26 rows.
        ;;  each row is 132 characters wide.
        ;; inputs: l=row index
        ;; outputs: de=row address, hl=row address
        ;; affects: af, de, hl
_avdc_rowptr_raw::
        ld      h,#0
        add     hl,hl
        call    .avdc_read_at_pointer
        push    de
        inc     hl
        call    .avdc_read_at_pointer
        ld      h,e
        pop     de
        ld      l,e
        ld      d,h
        ld      e,l
        ret
