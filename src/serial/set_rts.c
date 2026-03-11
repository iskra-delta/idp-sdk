/*
 * set_rts.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void serial_set_rts(sio_port *port, bool state) {
    if (state && (port->wr5 & 2) == 0) {
        z80_port_out(port->addr, 5);
        port->wr5 = (uint8_t)(port->wr5 | 2);
        z80_port_out(port->addr, port->wr5);
    } else if (!state && (port->wr5 & 2) != 0) {
        z80_port_out(port->addr, 5);
        port->wr5 = (uint8_t)(port->wr5 - 2);
        z80_port_out(port->addr, port->wr5);
    }
}
