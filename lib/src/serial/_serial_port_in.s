        ;; _serial_port_in.s
        ;;
        ;; Read one byte from an arbitrary Z80 I/O port for serial internals.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        .module _serial_port_in

        .globl  __serial_port_in

        .area   _CODE

        ;; uint8_t _serial_port_in(uint8_t port)
__serial_port_in::
        ld      c,a
        in      l,(c)
        ret
