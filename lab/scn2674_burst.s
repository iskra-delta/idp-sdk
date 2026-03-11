        ;; scn2674_burst.s
        ;;
        ;; Partner SCN2674 burst write helper.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_burst

        .globl  _scn2674_burst
        .globl  _scn2674_wait_mem_acc
        .globl  _scn2674_wait_rdy

        .include "../src/partner/scn2674.inc"

        .area   _CODE

        ;; scn2674_burst
        ;; writes a burst of chars with one attribute
        ;; NOTES:
        ;;  writes count characters from chars using the
        ;;  same attribute byte while periodically waiting
        ;;  for a safe memory access window
        ;; inputs: hl=chars; attr at sp+2, count at sp+3 (at function entry)
        ;; outputs: none
        ;; affects: af, bc, de, hl
_scn2674_burst::
        push    hl               ; after push: attr at sp+4, count at sp+5
        ld      hl,#4
        add     hl,sp
        ld      e,(hl)           ; E = attr (from sp+4)
        inc     hl
        ld      b,(hl)           ; B = count (from sp+5)
        pop     hl               ; restore HL = chars
        ex      af,af'
        ld      a,#MAX_BURST_CYCLE
        ex      af,af'
        call    _scn2674_wait_mem_acc
.burst_loop:
        ex      af,af'
        dec     a
        jr      nz,.burst_skip
        ld      a,#MAX_BURST_CYCLE
        call    _scn2674_wait_mem_acc
.burst_skip:
        ex      af,af'
        call    _scn2674_wait_rdy
        ld      a,(hl)
        inc     hl
        out     (SCN2674_CHR),a
        ld      a,e
        out     (SCN2674_AT),a
        call    _scn2674_wait_rdy
        ld      a,#SCN2674_CMD_WAC
        out     (SCN2674_CMD),a
        djnz    .burst_loop
        ret
