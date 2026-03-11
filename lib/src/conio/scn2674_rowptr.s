        ;; scn2674_rowptr.s
        ;;
        ;; Partner SCN2674 cached row lookup.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_rowptr

        .globl  _scn2674_rowptr
        .globl  _scn2674_cache_rows
        .globl  _scn2674_rowptr_raw
        .globl  __scn2674_row_cache
        .globl  __scn2674_row_cache_valid

        .area   _CODE

        ;; scn2674_rowptr
        ;; returns row address
        ;; NOTES:
        ;;  lazily fills the row-pointer cache on first use
        ;;  and then serves subsequent lookups from RAM
        ;; inputs: a=row index
        ;; outputs: de=row address
        ;; affects: af, bc, de, hl
_scn2674_rowptr::
        ld      c,a
        ld      a,(__scn2674_row_cache_valid)
        or      a
        jr      nz,.rowptr_cached
        push    bc
        call    _scn2674_cache_rows
        pop     bc
.rowptr_cached:
        ld      l,c
        ld      h,#0
        add     hl,hl
        ld      bc,#__scn2674_row_cache
        add     hl,bc
        ld      e,(hl)
        inc     hl
        ld      d,(hl)
        ret
