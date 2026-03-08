        ;; avdc_show_cursor.s
        ;;
        ;; Partner AVDC cursor enable wrapper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_show_cursor

        .globl  _avdc_show_cursor
        .globl  _avdc_wait_mem_acc
        .globl  _scn2674_cursor_on

        .area   _CODE

        ;; avdc_show_cursor
        ;; enables the text cursor
        ;; NOTES:
        ;;  waits for a safe memory access window before
        ;;  sending the cursor-on command
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_avdc_show_cursor::
        call    _avdc_wait_mem_acc
        jp      _scn2674_cursor_on
