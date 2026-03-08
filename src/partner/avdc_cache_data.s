        ;; avdc_cache_data.s
        ;;
        ;; Partner AVDC cached row storage.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_cache_data

        .globl  __avdc_row_cache
        .globl  __avdc_row_cache_valid

        .area   _DATA

__avdc_row_cache:
        .ds     52

__avdc_row_cache_valid:
        .ds     1
