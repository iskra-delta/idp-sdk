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
        ;;
        ;; Save both register banks onto the stack, copy the contiguous parts
        ;; into z80_registers_t with LDIR, then restore everything by popping
        ;; the same values back.
        ;;
        ;; The push order below is chosen so the saved frame at SP is:
        ;;   +00 AF
        ;;   +02 BC
        ;;   +04 DE
        ;;   +06 HL
        ;;   +08 IX
        ;;   +10 IY
        ;;   +12 AF'
        ;;   +14 BC'
        ;;   +16 DE'
        ;;   +18 HL'
        ;;   +20 return address (used as PC snapshot)
        ;;
        ;; That means the public struct is split into two contiguous blocks:
        ;;   1. AF..IY        -> stack +00 .. +11
        ;;   2. AF'..HL'      -> stack +12 .. +19
        ;;
        ;; SP, PC, I and R are not part of those contiguous stack blocks, so
        ;; they are stored separately between the two LDIR copies.
_z80_read_regs::
        ;; Save shadow register set first so the final frame starts with AF.
        exx
        push    hl
        push    de
        push    bc
        exx
        ex      af,af'
        push    af
        ex      af,af'

        ;; Save main register set last so it appears first in memory at SP.
        push    iy
        push    ix
        push    hl
        push    de
        push    bc
        push    af

        ;; IX is now free to use as a stable base pointer into the saved frame.
        ld      ix,#0
        add     ix,sp

        ;; Copy AF..IY from stack to z80_registers_t.
        ld      de,#_z80_registers_cache
        ld      hl,#0
        add     hl,sp
        ld      bc,#12
        ldir

        ;; Save caller SP before CALL z80_read_regs.
        ;; Current SP points at saved AF, so caller SP is SP + 22 bytes:
        ;;   20 bytes of saved registers + 2-byte return address.
        push    ix
        pop     hl
        ld      de,#22
        add     hl,de
        ld      a,l
        ld      (_z80_registers_cache + 12),a
        ld      a,h
        ld      (_z80_registers_cache + 13),a

        ;; Save PC from the return address that CALL placed above the frame.
        ld      a,20(ix)
        ld      (_z80_registers_cache + 14),a
        ld      a,21(ix)
        ld      (_z80_registers_cache + 15),a

        ;; Copy AF'..HL' from stack to z80_registers_t.
        ld      hl,#12
        add     hl,sp
        ld      de,#(_z80_registers_cache + 16)
        ld      bc,#8
        ldir

        ;; I and R are read directly; they are not available via stack pushes.
        ld      a,i
        ld      (_z80_registers_cache + 24),a
        ld      a,r
        ld      (_z80_registers_cache + 25),a

        ;; Restore main register set.
        pop     af
        pop     bc
        pop     de
        pop     hl
        pop     ix
        pop     iy

        ;; Restore shadow register set.
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
