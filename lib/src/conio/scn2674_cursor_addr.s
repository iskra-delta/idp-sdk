        ;; scn2674_cursor_addr.s
        ;;
        ;; Partner SCN2674 cursor-address helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_cursor_addr

        .globl  _scn2674_cursor_addr
        .globl  _scn2674_get_cursor

        .area   _CODE

        ;; scn2674_cursor_addr
        ;; returns current cursor address
        ;; NOTES:
        ;;  provides the Partner video layer access to the
        ;;  current cursor address
        ;; inputs: none
        ;; outputs: de=cursor address
        ;; affects: af, de
_scn2674_cursor_addr::
        call    _scn2674_get_cursor
        ret
