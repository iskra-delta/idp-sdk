        ;; rtc_reset.s
        ;;
        ;; Partner RTC reset helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module rtc_reset

        .globl  _rtc_reset

        .include "rtc.inc"

        .area   _CODE

        ;; rtc_reset
        ;; reset the running clock before programming new values
        ;; NOTES:
        ;;  issues the GO command used by Partner firmware
        ;;  before writing new RTC values
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_rtc_reset::
        ld      a,#0xff
        out     (MM58167A_GO),a
        ret
