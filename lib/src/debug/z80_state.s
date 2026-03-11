        ;; z80_state.s
        ;;
        ;; Storage for Z80 register snapshots.
        ;;
        ;; MIT License (see: LICENSE)
        ;; Copyright (c) 2026 Tomaz Stih
        ;;
        .module z80_state

        .globl  _z80_registers_cache

        .area   _DATA

_z80_registers_cache::
        .ds     26
