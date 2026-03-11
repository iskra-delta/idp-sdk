        ;; scn2674_hide_cursor.s
        ;;
        ;; Partner SCN2674 cursor disable wrapper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_hide_cursor

        .globl  _scn2674_hide_cursor
        .globl  _scn2674_wait_mem_acc
        .globl  _scn2674_cursor_off

        .area   _CODE

        ;; scn2674_hide_cursor
        ;; disables the text cursor
        ;; NOTES:
        ;;  waits for a safe memory access window before
        ;;  sending the cursor-off command
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_scn2674_hide_cursor::
        call    _scn2674_wait_mem_acc
        jp      _scn2674_cursor_off
