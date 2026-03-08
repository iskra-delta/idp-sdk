        ;; avdc_xy.s
        ;;
        ;; Partner AVDC cursor positioning.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_xy

        .globl  _avdc_xy
        .globl  _avdc_wait_mem_acc
        .globl  _avdc_rowptr_raw
        .globl  _scn2674_set_cursor

        .area   _CODE

        ;; avdc_xy
        ;; moves cursor to x,y
        ;; NOTES:
        ;;  resolves the row start address from y and
        ;;  then adds x to position the cursor
        ;; inputs: stack args x, y
        ;; outputs: none
        ;; affects: af, bc, de, hl
_avdc_xy::
        pop     de
        pop     bc
        pop     hl
        push    hl
        push    bc
        push    de
        ld      h,c
        call    _avdc_wait_mem_acc
        ld      c,h
        ld      a,l
        call    _avdc_rowptr_raw
        ld      d,#0
        ld      e,c
        add     hl,de
        push    hl
        call    _scn2674_set_cursor
        ret
