        ;; rtc_reset_nvram.s
        ;;
        ;; Partner RTC NVRAM-flag reset helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module rtc_reset_nvram

        .globl  _rtc_reset_nvram

        .include "rtc.inc"

        .area   _CODE

        ;; rtc_reset_nvram
        ;; reset rtc nvram flags
        ;; NOTES:
        ;;  clears partner-specific nvram flag state
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_rtc_reset_nvram::
        ld      a,#0xff
        out     (MM58167A_RESET_NVRAM),a
        ret
