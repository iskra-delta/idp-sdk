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
        .globl  _scn2674_rowptr_raw
        .globl  __scn2674_row_cache

        .area   _CODE

        ;; scn2674_rowptr
        ;; returns row address
        ;; NOTES:
        ;;  serves row lookups from the cache prepared by
        ;;  conio initialization
        ;; inputs: a=row index
        ;; outputs: de=row address
        ;; affects: af, bc, de, hl
_scn2674_rowptr::
        ld      c,a
        ld      l,c
        ld      h,#0
        add     hl,hl
        ld      bc,#__scn2674_row_cache
        add     hl,bc
        ld      e,(hl)
        inc     hl
        ld      d,(hl)
        ret
