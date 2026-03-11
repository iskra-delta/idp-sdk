        ;; bcd2bin.s
        ;;
        ;; 8-bit BCD to binary conversion.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 22.06.2021    tstih
        .module bcd2bin

        .globl  _bcd2bin

        .area   _CODE

        ;; bcd2bin
        ;; convert bcd number to binary
        ;; NOTES:
        ;;  converts one packed bcd value to binary
        ;; inputs: a=bcd
        ;; outputs: l=binary value
        ;; affects: af, bc, hl
_bcd2bin::
        ld      c,a
        and     #0xf0
        srl     a
        ld      b,a
        srl     a
        srl     a
        add     a,b
        ld      b,a
        ld      a,c
        and     #0x0f
        add     a,b
        ld      l,a
        ret
