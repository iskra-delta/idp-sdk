        ;; scn2674_puts_burst.s
        ;;
        ;; Partner SCN2674 burst character write.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        .module scn2674_puts_burst

        .globl  _scn2674_puts_burst
        .globl  _scn2674_wait_mem_acc
        .globl  _scn2674_wait_rdy

        .include "scn2674.inc"

        .area   _CODE

        ;; void scn2674_puts_burst(const char *s, uint8_t len, unsigned char attr)
        ;; writes a short printable run at the current cursor
        ;; NOTES:
        ;;  aligns to a memory-access window once, then refreshes
        ;;  that alignment every MAX_BURST_CYCLE characters while
        ;;  using the cheaper ready wait between characters
        ;; inputs: hl=s, stack: len, attr
        ;; outputs: none
        ;; affects: af, bc, de, hl
_scn2674_puts_burst::
        pop     bc              ; BC = return address
        pop     de              ; E = len, D = attr
        push    bc

        ld      a,e
        or      a
        ret     z

        ld      b,d             ; B = attr
        ld      c,e             ; C = remaining length
        ld      e,#MAX_BURST_CYCLE

        call    _scn2674_wait_mem_acc

.loop:
        call    _scn2674_wait_rdy
        ld      a,(hl)
        out     (SCN2674_CHR),a
        ld      a,b
        out     (SCN2674_AT),a
        call    _scn2674_wait_rdy
        call    _scn2674_wait_rdy
        ld      a,#SCN2674_CMD_WAC
        out     (SCN2674_CMD),a
        inc     hl
        dec     c
        ret     z
        dec     e
        jr      nz,.loop

        call    _scn2674_wait_mem_acc
        ld      e,#MAX_BURST_CYCLE
        jr      .loop
