/*
 * send.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_send(sio_port *port) {
    while (serial_check_able_to_send(port) && !serial_buffer_empty(&port->buffer_out)) {
        while (!serial_check_tx_buffer_empty(port)) {
        }
        z80_port_out((uint8_t)(port->addr - 1), serial_buffer_get_ch(&port->buffer_out));
    }
    return serial_buffer_empty(&port->buffer_out);
}
