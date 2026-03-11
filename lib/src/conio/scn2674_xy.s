        ;; scn2674_xy.s
        ;;
        ;; Partner SCN2674 cursor positioning.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_xy

        .globl  _scn2674_xy
        .globl  _scn2674_wait_mem_acc
        .globl  _scn2674_rowptr_raw
        .globl  _scn2674_set_cursor

        .area   _CODE

        ;; scn2674_xy
        ;; moves cursor to x,y
        ;; NOTES:
        ;;  resolves the row start address from y and
        ;;  then adds x to position the cursor
        ;; inputs: hl=x, de=y
        ;; outputs: none
        ;; affects: af, bc, de, hl
_scn2674_xy::
        ld      c,l              ; C = x (low byte; only low byte used)
        ld      l,e              ; L = y (row index)
        call    _scn2674_wait_mem_acc
        call    _scn2674_rowptr_raw
        ld      d,#0
        ld      e,c              ; DE = x (column offset)
        add     hl,de            ; HL = row_addr + x = cursor address
        call    _scn2674_set_cursor
        ret
