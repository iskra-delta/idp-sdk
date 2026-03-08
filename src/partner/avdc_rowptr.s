        ;; avdc_rowptr.s
        ;;
        ;; Partner AVDC cached row lookup.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_rowptr

        .globl  _avdc_rowptr
        .globl  _avdc_cache_rows
        .globl  __avdc_row_cache
        .globl  __avdc_row_cache_valid

        .area   _CODE

        ;; avdc_rowptr
        ;; returns cached row address
        ;; NOTES:
        ;;  lazily fills the row-pointer cache on first use
        ;;  and returns the cached row start address
        ;; inputs: a=row index
        ;; outputs: de=row address
        ;; affects: af, bc, de, hl
_avdc_rowptr::
        ld      c,a
        ld      a,(__avdc_row_cache_valid)
        or      a
        jr      nz,.rowptr_cached
        push    bc
        call    _avdc_cache_rows
        pop     bc
.rowptr_cached:
        ld      l,c
        ld      h,#0
        add     hl,hl
        ld      bc,#__avdc_row_cache
        add     hl,bc
        ld      e,(hl)
        inc     hl
        ld      d,(hl)
        ret
