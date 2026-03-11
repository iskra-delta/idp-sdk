        ;; z80_port_out.s
        ;;
        ;; Write one byte to an arbitrary Z80 I/O port.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module z80_port_out

        .globl  _z80_port_out

        .area   _CODE

        ;; void z80_port_out(uint8_t port, uint8_t value)
        ;; inputs: a=port, l=value
        ;; outputs: none
        ;; affects: af, bc
_z80_port_out::
        ld      c,a
        ld      a,l
        out     (c),a
        ret
