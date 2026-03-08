        ;; avdc_cursor_addr.s
        ;;
        ;; Partner AVDC cursor-address helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_cursor_addr

        .globl  _avdc_cursor_addr
        .globl  _scn2674_get_cursor

        .area   _CODE

        ;; avdc_cursor_addr
        ;; returns current cursor address
        ;; NOTES:
        ;;  provides the Partner video layer access to the
        ;;  current cursor address
        ;; inputs: none
        ;; outputs: de=cursor address
        ;; affects: af, de, hl
_avdc_cursor_addr::
        call    _scn2674_get_cursor
        ld      d,h
        ld      e,l
        ret
