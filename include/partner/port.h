/*
 * port.h
 *
 * Generic Z80 I/O port access helpers.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#ifndef __PARTNER_PORT_H__
#define __PARTNER_PORT_H__

#include <stdint.h>

/* Read one byte from an I/O port. */
uint8_t port_in(uint8_t port);

/* Write one byte to an I/O port. */
void port_out(uint8_t port, uint8_t value);

#endif /* __PARTNER_PORT_H__ */
