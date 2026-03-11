/*
 * check_able_to_send.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_check_able_to_send(sio_port *port) {
    if (port->flow_control == SIO_FLOW_CONTROL_RTSCTS) {
        return serial_check_cts(port);
    }
    if (port->flow_control == SIO_FLOW_CONTROL_XONXOFF) {
        return port->xon_send;
    }
    return true;
}
