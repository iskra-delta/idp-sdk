/*
 * check_cts.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool serial_check_cts(sio_port *port) {
    return (_serial_port_in(_serial_ctrl_port(port->addr)) & Z80SIO_RR0_CTS) != 0;
}
