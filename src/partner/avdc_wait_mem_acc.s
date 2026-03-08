        ;; avdc_wait_mem_acc.s
        ;;
        ;; Partner AVDC memory-access wait.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2022 Tomaz Stih
        ;;
        ;; 05.05.2022   tstih
        ;;
        .module avdc_wait_mem_acc

        .globl  _avdc_wait_mem_acc

        .include "avdc.inc"

        .area   _CODE

        ;; avdc_wait_mem_acc
        ;; waits for AVDC memory access window
        ;; NOTES:
        ;;  waits for the SCN2674A memory access signal
        ;;  to assert and then deassert before returning
        ;; inputs: none
        ;; outputs: none
        ;; affects: af
_avdc_wait_mem_acc::
        in      a,(#SCN2674_GR_CMNI)
        and     #SCN2674_GR_CMNI_SCN2674A
        jr      z,_avdc_wait_mem_acc
.wait_mem_acc:
        in      a,(#SCN2674_GR_CMNI)
        and     #SCN2674_GR_CMNI_SCN2674A
        jr      nz,.wait_mem_acc
        ret
