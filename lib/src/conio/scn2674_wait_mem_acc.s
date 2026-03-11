        ;; scn2674_wait_mem_acc.s
        ;;
        ;; Partner SCN2674 memory-access wait.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module scn2674_wait_mem_acc

        .globl  _scn2674_wait_mem_acc

        .include "scn2674.inc"

        .area   _CODE

        ;; scn2674_wait_mem_acc
        ;; waits for SCN2674 memory access window
        ;; NOTES:
        ;;  waits for the SCN2674A memory access signal
        ;;  to assert and then deassert before returning
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_scn2674_wait_mem_acc::
        in      a,(#SCN2674_GR_CMNI)
        and     #SCN2674_GR_CMNI_SCN2674A
        jr      z,_scn2674_wait_mem_acc
.wait_mem_acc:
        in      a,(#SCN2674_GR_CMNI)
        and     #SCN2674_GR_CMNI_SCN2674A
        jr      nz,.wait_mem_acc
        ret
