/*
 * z80.h
 *
 * Z80 chip-level declarations.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 11.03.2026   tstih
 *
 */
#ifndef __PARTNER_CHIPS_Z80_H__
#define __PARTNER_CHIPS_Z80_H__

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

/* Read one byte from an I/O port. */
extern uint8_t z80_port_in(uint8_t port);

/* Write one byte to an I/O port. */
extern void z80_port_out(uint8_t port, uint8_t value);

/* Capture a snapshot of the current Z80 register state. */
extern const z80_registers_t *z80_read_regs(void);

/* Read one byte from an arbitrary memory address. */
extern uint8_t z80_read_mem(uint16_t address);

/* Read a block of bytes from memory into a caller-provided buffer. */
extern void z80_read_mem_block(uint8_t *dest, uint16_t source, uint16_t len);

#endif /* __PARTNER_CHIPS_Z80_H__ */
