/*
 * exchange.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

sio_exit_code serial_exchange(sio_port *port) {
    uint8_t ch;
    uint16_t loop_count = 0;

    if (port->buffer_in.count >= port->buffer_in.size - port->in_buffer_ext) {
        return port->buffer_in.count >= port->buffer_in.size
            ? SIO_EXIT_CODE_BUFFER_OVERFLOW
            : SIO_EXIT_CODE_BUFFER_FULL;
    }

    serial_set_able_to_rcv(port, true);
    for (;;) {
        if (serial_check_able_to_send(port) && !serial_buffer_empty(&port->buffer_out)) {
            loop_count = 0;
            if (serial_check_tx_buffer_empty(port)) {
                z80_port_out((uint8_t)(port->addr - 1), serial_buffer_get_ch(&port->buffer_out));
            }
        }

        if (serial_check_ch_available(port)) {
            loop_count = 0;
            ch = z80_port_in((uint8_t)(port->addr - 1));
            if (port->flow_control == SIO_FLOW_CONTROL_XONXOFF &&
                (ch == SIO_CHAR_XON || ch == SIO_CHAR_XOFF)) {
                port->xon_send = (ch == SIO_CHAR_XON);
            } else {
                serial_buffer_put_ch(&port->buffer_in, ch);
                if (port->buffer_in.count >= port->buffer_in.size - port->in_buffer_ext) {
                    serial_set_able_to_rcv(port, false);
                    return serial_flush(port);
                }
            }
        } else {
            loop_count++;
            if (loop_count >= port->no_activity_thr) {
                serial_set_able_to_rcv(port, false);
                return serial_flush(port);
            }
        }
    }
}
