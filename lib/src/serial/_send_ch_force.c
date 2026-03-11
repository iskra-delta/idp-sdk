/*
 * _send_ch_force.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void _serial_send_ch_force(sio_port *port, uint8_t ch) {
    while (!_serial_check_tx_buffer_empty(port)) {
    }
    _serial_port_out(_serial_data_port(port->addr), ch);
}
