/*
 * check_ch_available.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_check_ch_available(sio_port *port) {
    return (z80_port_in(port->addr) & Z80SIO_RR0_RX_AVAIL) != 0;
}
