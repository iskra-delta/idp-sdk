        ;; avdc_cache_rows.s
        ;;
        ;; Partner AVDC row-table cache fill.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_cache_rows

        .globl  _avdc_cache_rows
        .globl  _avdc_rowptr_raw
        .globl  __avdc_row_cache
        .globl  __avdc_row_cache_valid

        .area   _CODE

        ;; avdc_cache_rows
        ;; caches the current row table in RAM
        ;; NOTES:
        ;;  reads all 26 row pointers and stores them for
        ;;  later fast lookup through avdc_rowptr
        ;; inputs: none
        ;; outputs: none
        ;; affects: af, bc, de, hl
_avdc_cache_rows::
        ld      c,#0
.cache_loop:
        ld      l,c
        call    _avdc_rowptr_raw
        ld      l,c
        ld      h,#0
        add     hl,hl
        ld      bc,#__avdc_row_cache
        add     hl,bc
        ld      (hl),e
        inc     hl
        ld      (hl),d
        ld      a,c
        inc     a
        ld      c,a
        cp      #26
        jr      c,.cache_loop
        ld      a,#1
        ld      (__avdc_row_cache_valid),a
        ret
