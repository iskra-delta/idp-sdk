        ;; rtc.inc
        ;;
        ;; Partner-specific MM58167A port map.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih

        ;; --- 0xA0-0xA7 - MM58167A time registers (BCD) ----------------------
        .equ MM58167A_THOUS_S,         0xA0
        .equ MM58167A_HUNDR_S,         0xA1
        .equ MM58167A_SECOND,          0xA2
        .equ MM58167A_MINUTE,          0xA3
        .equ MM58167A_HOUR,            0xA4
        .equ MM58167A_WDAY,            0xA5
        .equ MM58167A_MDAY,            0xA6
        .equ MM58167A_MONTH,           0xA7

        ;; --- 0xA8-0xAF - MM58167A alarm / nvram registers -------------------
        .equ MM58167A_YEAR,            0xA9

        ;; --- 0xB0-0xBF - MM58167A status / control --------------------------
        .equ MM58167A_INT_STATUS,      0xB0
        .equ MM58167A_INT_CONTROL,     0xB1
        .equ MM58167A_RESET_COUNTER,   0xB2
        .equ MM58167A_RESET_NVRAM,     0xB3
        .equ MM58167A_STATUS,          0xB4
        .equ MM58167A_GO,              0xB5
        .equ MM58167A_TEST,            0xBF
