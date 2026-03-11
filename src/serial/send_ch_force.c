/*
 * send_ch_force.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void serial_send_ch_force(sio_port *port, uint8_t ch) {
    while (!serial_check_tx_buffer_empty(port)) {
    }
    z80_port_out((uint8_t)(port->addr - 1), ch);
}
