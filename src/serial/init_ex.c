/*
 * init_ex.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include <stdlib.h>

#include "common.h"

sio_port *serial_init_ex(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity,
    sio_flow_control flow_control, uint16_t out_buffer_sz,
    uint16_t in_buffer_sz, uint16_t in_buffer_ext, uint16_t no_activity_thr) {
    sio_port *port;
    uint8_t i;

    for (i = 1; i < 11; i++) {
        z80_port_out(port_addr, serial_init_value(i, mode, bauds, data_bits, stop_bits, parity));
    }

    port = calloc(1, sizeof(sio_port));
    if (!port) {
        return NULL;
    }

    serial_buffer_alloc_internal(&port->buffer_in, (uint16_t)(in_buffer_sz + in_buffer_ext));
    serial_buffer_alloc_internal(&port->buffer_out, out_buffer_sz);
    port->in_buffer_ext = in_buffer_ext;
    port->no_activity_thr = no_activity_thr;
    port->addr = port_addr;
    port->wr5 = serial_init_wr5_default();
    port->flow_control = flow_control;
    port->xon_send = true;
    port->xon_rcv = true;
    return port;
}
