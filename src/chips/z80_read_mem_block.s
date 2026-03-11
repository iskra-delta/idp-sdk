        ;; z80_read_mem_block.s
        ;;
        ;; Read a block of bytes from an arbitrary memory address.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 11.03.2026   tstih
        ;;
        .module z80_read_mem_block

        .globl  _z80_read_mem_block

        .area   _CODE

        ;; void z80_read_mem_block(uint8_t *dest, uint16_t source, uint16_t len)
        ;; inputs:
        ;;   hl = dest
        ;;   de = source
        ;;   len = sp + 2
        ;; notes:
        ;;   LDIR copies from HL to DE, so swap the first two arguments and
        ;;   load BC with the caller-supplied byte count from the stack.
_z80_read_mem_block::
        ex      de,hl
        ld      iy,#2
        add     iy,sp
        ld      c,0(iy)
        ld      b,1(iy)
        ldir
        ret
