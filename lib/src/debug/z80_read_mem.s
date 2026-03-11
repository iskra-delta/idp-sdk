        ;; z80_read_mem.s
        ;;
        ;; Read one byte from an arbitrary memory address.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 11.03.2026   tstih
        ;;
        .module z80_read_mem

        .globl  _z80_read_mem

        .area   _CODE

        ;; uint8_t z80_read_mem(uint16_t address)
        ;; inputs: hl=address
        ;; outputs: a=value
        ;; affects: af
_z80_read_mem::
        ld      a,(hl)
        ret
