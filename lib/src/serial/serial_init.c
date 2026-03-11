/*
 * init.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

sio_port *serial_init(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity,
    sio_flow_control flow_control) {
    return serial_init_ex(port_addr, mode, bauds, data_bits, stop_bits, parity,
        flow_control, 512, 128, 64, 100);
}
