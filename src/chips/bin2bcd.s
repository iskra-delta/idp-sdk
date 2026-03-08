        ;; bin2bcd.s
        ;;
        ;; 8-bit binary to BCD conversion.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 22.06.2021    tstih
        .module bin2bcd

        .globl  _bin2bcd

        .area   _CODE

        ;; bin2bcd
        ;; convert binary number to bcd
        ;; NOTES:
        ;;  converts one 8-bit value to packed bcd
        ;; inputs: stack arg bin
        ;; outputs: l=bcd value
        ;; affects: af, bc, hl
_bin2bcd::
        ld      hl,#2
        add     hl,sp
        ld      a,(hl)
        ld      c,a
        ld      b,#0x08
        xor     a
.b2bloop:
        sla     c
        adc     a,a
        daa
        djnz    .b2bloop
        ld      l,a
        ret
