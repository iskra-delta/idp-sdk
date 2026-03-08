        ;; scn2674_cursor_on.s
        ;;
        ;; Raw SCN2674 cursor enable.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_cursor_on

        .globl  _scn2674_cursor_on
        .globl  _scn2674_wait_rdy

        .include "../partner/avdc.inc"

        .area   _CODE

        ;; scn2674_cursor_on
        ;; enables the text cursor
        ;; NOTES:
        ;;  sends the cursor-on command to the controller
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_scn2674_cursor_on::
        call    _scn2674_wait_rdy
        ld      a,#SCN2674_CMD_CURS_ON
        out     (SCN2674_CMD),a
        ret
