/*
 * check_tx_buffer_empty.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_check_tx_buffer_empty(sio_port *port) {
    return (z80_port_in(port->addr) & Z80SIO_RR0_TX_EMPTY) != 0;
}
