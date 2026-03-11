        ;; z80_port_in.s
        ;;
        ;; Read one byte from an arbitrary Z80 I/O port.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 08.03.2026   tstih
        ;;
        .module z80_port_in

        .globl  _z80_port_in

        .area   _CODE

        ;; uint8_t z80_port_in(uint8_t port)
        ;; inputs: a=port
        ;; outputs: l=value
        ;; affects: af, bc, hl
_z80_port_in::
        ld      c,a
        in      l,(c)
        ret
