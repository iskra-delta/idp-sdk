        ;; scn2674_cursor_off.s
        ;;
        ;; Raw SCN2674 cursor disable.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_cursor_off

        .globl  _scn2674_cursor_off
        .globl  _scn2674_wait_rdy

        .include "scn2674.inc"

        .area   _CODE

        ;; scn2674_cursor_off
        ;; disables the text cursor
        ;; NOTES:
        ;;  sends the cursor-off command to the controller
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_scn2674_cursor_off::
        call    _scn2674_wait_rdy
        ld      a,#SCN2674_CMD_CURS_OFF
        out     (SCN2674_CMD),a
        ret
