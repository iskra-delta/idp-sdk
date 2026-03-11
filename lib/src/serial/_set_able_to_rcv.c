/*
 * _set_able_to_rcv.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

void _serial_set_able_to_rcv(sio_port *port, bool state) {
    if (port->flow_control == SIO_FLOW_CONTROL_RTSCTS) {
        serial_set_rts(port, state);
    } else if (port->flow_control == SIO_FLOW_CONTROL_XONXOFF) {
        if (state && !port->xon_rcv) {
            _serial_send_ch_force(port, SIO_CHAR_XON);
            port->xon_rcv = true;
        } else if (!state && port->xon_rcv) {
            _serial_send_ch_force(port, SIO_CHAR_XOFF);
            port->xon_rcv = false;
        }
    }
}
