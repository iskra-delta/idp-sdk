        ;; scn2674_wait_rdy.s
        ;;
        ;; Raw SCN2674 ready-state polling.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_wait_rdy

        .globl  _scn2674_wait_rdy

        .include "../partner/avdc.inc"

        .area   _CODE

        ;; scn2674_wait_rdy
        ;; waits for SCN2674 ready state
        ;; NOTES:
        ;;  polls the SCN2674 status register until the
        ;;  ready bit becomes set
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_scn2674_wait_rdy::
        in      a,(#SCN2674_STS)
        and     #SCN2674_STS_RDY
        jr      z,_scn2674_wait_rdy
        ret
