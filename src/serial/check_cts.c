/*
 * check_cts.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_check_cts(sio_port *port) {
    return (z80_port_in(port->addr) & Z80SIO_RR0_CTS) != 0;
}
