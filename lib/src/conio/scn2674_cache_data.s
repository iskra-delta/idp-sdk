        ;; scn2674_cache_data.s
        ;;
        ;; Partner SCN2674 cached row storage.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_cache_data

        .globl  __scn2674_row_cache
        .globl  __scn2674_row_cache_valid

        .area   _DATA

__scn2674_row_cache:
        .ds     52

__scn2674_row_cache_valid:
        .ds     1
