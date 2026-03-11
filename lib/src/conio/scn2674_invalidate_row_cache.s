        ;; scn2674_invalidate_row_cache.s
        ;;
        ;; Partner SCN2674 row-cache invalidation.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_invalidate_row_cache

        .globl  _scn2674_invalidate_row_cache
        .globl  __scn2674_row_cache_valid

        .area   _CODE

        ;; scn2674_invalidate_row_cache
        ;; marks cached row pointers as stale
        ;; NOTES:
        ;;  forces the next scn2674_rowptr call to reread the
        ;;  row table from hardware
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_scn2674_invalidate_row_cache::
        xor     a
        ld      (__scn2674_row_cache_valid),a
        ret
