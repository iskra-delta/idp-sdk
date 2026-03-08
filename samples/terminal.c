/*
 * terminal.c
 *
 * Simple serial terminal demo for SIO channel B.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#include <stdint.h>

#include <partner.h>

void main(void) {
    sio_port *port;
    int ch;

    clrscr();
    cputs("Partner serial terminal on SIO B.\r\n");
    cputs("Press ESC to quit.\r\n");

    port = serial_init(
        SIO_PORT_LPT,
        SIO_MODE_POLLING,
        SIO_BAUDS_9600,
        SIO_DATA_BITS_8,
        SIO_STOP_BITS_1,
        SIO_PARITY_NONE,
        SIO_FLOW_CONTROL_NONE
    );

    if (!port) {
        cputs("serial_init failed.\r\n");
        return;
    }

    for (;;) {
        ch = kbhit();
        if (ch) {
            if (ch == 27) {
                break;
            }
            serial_buffer_put_ch(&port->buffer_out, (uint8_t)ch);
            serial_send(port);
        }

        (void)serial_exchange(port);

        while (!serial_buffer_empty(&port->buffer_in)) {
            putch(serial_buffer_get_ch(&port->buffer_in));
        }
    }

    serial_done(port);
    cputs("\r\nDone.\r\n");
}
