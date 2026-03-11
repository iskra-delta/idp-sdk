/*
 * debug.h
 *
 * Public debug and inspection services.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#ifndef __PARTNER_DEBUG_H__
#define __PARTNER_DEBUG_H__

#include <stdint.h>

typedef struct z80_registers_s {
    uint16_t af;
    uint16_t bc;
    uint16_t de;
    uint16_t hl;
    uint16_t ix;
    uint16_t iy;
    uint16_t sp;
    uint16_t pc;
    uint16_t af_shadow;
    uint16_t bc_shadow;
    uint16_t de_shadow;
    uint16_t hl_shadow;
    uint8_t i;
    uint8_t r;
} z80_registers_t;

/* Read the current Z80 register snapshot. */
extern const z80_registers_t *z80_read_regs(void);

/* Read one byte from the requested memory address. */
extern uint8_t z80_read_mem(uint16_t address);

/* Copy a block of memory from the requested source address. */
extern void z80_read_mem_block(uint8_t *dest, uint16_t source, uint16_t len);

#endif /* __PARTNER_DEBUG_H__ */
