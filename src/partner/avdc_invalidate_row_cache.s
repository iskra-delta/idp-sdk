        ;; avdc_invalidate_row_cache.s
        ;;
        ;; Partner AVDC row-cache invalidation.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_invalidate_row_cache

        .globl  _avdc_invalidate_row_cache
        .globl  __avdc_row_cache_valid

        .area   _CODE

        ;; avdc_invalidate_row_cache
        ;; marks cached row pointers as stale
        ;; NOTES:
        ;;  forces the next avdc_rowptr call to reread the
        ;;  row table from hardware
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_avdc_invalidate_row_cache::
        xor     a
        ld      (__avdc_row_cache_valid),a
        ret
