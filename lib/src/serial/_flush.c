/*
 * _flush.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

sio_exit_code _serial_flush(sio_port *port) {
    uint16_t loop_count = 0;

    for (;;) {
        if (_serial_check_ch_available(port)) {
            uint8_t ch;

            loop_count = 0;
            ch = _serial_port_in(_serial_data_port(port->addr));
            if (port->flow_control == SIO_FLOW_CONTROL_XONXOFF &&
                (ch == SIO_CHAR_XON || ch == SIO_CHAR_XOFF)) {
                port->xon_send = (ch == SIO_CHAR_XON);
            } else {
                serial_buffer_put_ch(&port->buffer_in, ch);
                if (port->buffer_in.count >= port->buffer_in.size) {
                    return SIO_EXIT_CODE_BUFFER_OVERFLOW;
                }
            }
        } else {
            loop_count++;
            if (loop_count >= port->no_activity_thr) {
                return port->buffer_in.count >= port->buffer_in.size - port->in_buffer_ext
                    ? SIO_EXIT_CODE_BUFFER_FULL
                    : SIO_EXIT_CODE_NO_ACTIVITY;
            }
        }
    }
}
