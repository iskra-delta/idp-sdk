        ;; port_in.s
        ;;
        ;; Read one byte from an arbitrary I/O port.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module port_in

        .globl  _port_in

        .area   _CODE

        ;; uint8_t port_in(uint8_t port)
        ;; inputs: a=port
        ;; outputs: l=value
        ;; affects: af, bc, hl
_port_in::
        ld      c,a
        in      l,(c)
        ret
