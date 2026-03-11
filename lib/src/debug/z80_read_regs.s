        ;; z80_read_regs.s
        ;;
        ;; Capture a snapshot of the current Z80 registers.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        ;; 11.03.2026   tstih
        ;;
        .module z80_read_regs

        .globl  _z80_read_regs
        .globl  _z80_registers_cache

        .area   _CODE

        ;; const z80_registers_t *z80_read_regs(void)
        ;; outputs: de=&_z80_registers_cache
_z80_read_regs::
        exx
        push    hl
        push    de
        push    bc
        exx
        ex      af,af'
        push    af
        ex      af,af'

        push    iy
        push    ix
        push    hl
        push    de
        push    bc
        push    af

        ld      ix,#0
        add     ix,sp

        ld      de,#_z80_registers_cache
        ld      hl,#0
        add     hl,sp
        ld      bc,#12
        ldir

        push    ix
        pop     hl
        ld      de,#22
        add     hl,de
        ld      a,l
        ld      (_z80_registers_cache + 12),a
        ld      a,h
        ld      (_z80_registers_cache + 13),a

        ld      a,20(ix)
        ld      (_z80_registers_cache + 14),a
        ld      a,21(ix)
        ld      (_z80_registers_cache + 15),a

        ld      hl,#12
        add     hl,sp
        ld      de,#(_z80_registers_cache + 16)
        ld      bc,#8
        ldir

        ld      a,i
        ld      (_z80_registers_cache + 24),a
        ld      a,r
        ld      (_z80_registers_cache + 25),a

        pop     af
        pop     bc
        pop     de
        pop     hl
        pop     ix
        pop     iy

        ex      af,af'
        pop     af
        ex      af,af'
        exx
        pop     bc
        pop     de
        pop     hl
        exx

        ld      de,#_z80_registers_cache
        ret
