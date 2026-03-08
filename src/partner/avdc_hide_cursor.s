        ;; avdc_hide_cursor.s
        ;;
        ;; Partner AVDC cursor disable wrapper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_hide_cursor

        .globl  _avdc_hide_cursor
        .globl  _avdc_wait_mem_acc
        .globl  _scn2674_cursor_off

        .area   _CODE

        ;; avdc_hide_cursor
        ;; disables the text cursor
        ;; NOTES:
        ;;  waits for a safe memory access window before
        ;;  sending the cursor-off command
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_avdc_hide_cursor::
        call    _avdc_wait_mem_acc
        jp      _scn2674_cursor_off
