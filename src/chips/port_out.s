        ;; port_out.s
        ;;
        ;; Write one byte to an arbitrary I/O port.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module port_out

        .globl  _port_out

        .area   _CODE

        ;; void port_out(uint8_t port, uint8_t value)
        ;; inputs: a=port, l=value
        ;; outputs: none
        ;; affects: af, bc
_port_out::
        ld      c,a
        ld      a,l
        out     (c),a
        ret
