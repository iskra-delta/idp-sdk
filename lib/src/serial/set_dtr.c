/*
 * set_dtr.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void serial_set_dtr(sio_port *port, bool state) {
    uint8_t ctrl_port = _serial_ctrl_port(port->addr);

    if (state && (port->wr5 & 0x80) == 0) {
        _serial_port_out(ctrl_port, 5);
        port->wr5 = (uint8_t)(port->wr5 | 0x80);
        _serial_port_out(ctrl_port, port->wr5);
    } else if (!state && (port->wr5 & 0x80) != 0) {
        _serial_port_out(ctrl_port, 5);
        port->wr5 = (uint8_t)(port->wr5 & (uint8_t)~0x80);
        _serial_port_out(ctrl_port, port->wr5);
    }
}
