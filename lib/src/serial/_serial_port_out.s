        ;; _serial_port_out.s
        ;;
        ;; Write one byte to an arbitrary Z80 I/O port for serial internals.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        .module _serial_port_out

        .globl  __serial_port_out

        .area   _CODE

        ;; void _serial_port_out(uint8_t port, uint8_t value)
__serial_port_out::
        ld      c,a
        ld      a,l
        out     (c),a
        ret
