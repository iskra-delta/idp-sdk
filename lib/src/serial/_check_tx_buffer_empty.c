/*
 * _check_tx_buffer_empty.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

bool _serial_check_tx_buffer_empty(sio_port *port) {
    return (_serial_port_in(_serial_ctrl_port(port->addr)) & Z80SIO_RR0_TX_EMPTY) != 0;
}
