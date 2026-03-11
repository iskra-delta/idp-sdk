/*
 * send.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_send(sio_port *port) {
    while (_serial_check_able_to_send(port) && !serial_buffer_empty(&port->buffer_out)) {
        while (!_serial_check_tx_buffer_empty(port)) {
        }
        _serial_port_out(_serial_data_port(port->addr),
            serial_buffer_get_ch(&port->buffer_out));
    }
    return serial_buffer_empty(&port->buffer_out);
}
