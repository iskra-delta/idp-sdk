/*
 * serial.c
 *
 * Buffered Partner serial I/O over Z80 SIO.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#include <stdlib.h>

#include <partner/port.h>
#include <partner/hw/partner/serial.h>

#define SIO_CHAR_XON  17
#define SIO_CHAR_XOFF 19

/* Base Z80 SIO initialization sequence used by Partner firmware-style setup. */
static const uint8_t sio_init_str[] = {
    10,
    0x30,
    0x18,
    0x04,
    0x44,
    0x05,
    0x68,
    0x01,
    0x04,
    0x03,
    0xC1
};

/* Allocate backing storage for a ring buffer. */
static void serial_buffer_alloc_internal(sio_buffer *buffer, uint16_t size) {
    buffer->values = malloc(size);
    buffer->size = size;
}

/* Check whether the transmitter can accept the next byte. */
static bool serial_check_tx_buffer_empty(sio_port *port) {
    return (port_in(port->addr) & Z80SIO_RR0_TX_EMPTY) != 0;
}

/* Check whether a received byte is waiting in the SIO. */
static bool serial_check_ch_available(sio_port *port) {
    return (port_in(port->addr) & Z80SIO_RR0_RX_AVAIL) != 0;
}

/* Send one byte immediately, bypassing the output ring buffer. */
static void serial_send_ch_force(sio_port *port, uint8_t ch) {
    while (!serial_check_tx_buffer_empty(port)) {
    }
    port_out((uint8_t)(port->addr - 1), ch);
}

/* Evaluate current flow-control state before transmitting queued bytes. */
static bool serial_check_able_to_send(sio_port *port) {
    if (port->flow_control == SIO_FLOW_CONTROL_RTSCTS) {
        return serial_check_cts(port);
    }
    if (port->flow_control == SIO_FLOW_CONTROL_XONXOFF) {
        return port->xon_send;
    }
    return true;
}

/* Assert or withdraw receiver readiness according to the selected flow control. */
static void serial_set_able_to_rcv(sio_port *port, bool state) {
    if (port->flow_control == SIO_FLOW_CONTROL_RTSCTS) {
        serial_set_rts(port, state);
    } else if (port->flow_control == SIO_FLOW_CONTROL_XONXOFF) {
        if (state && !port->xon_rcv) {
            serial_send_ch_force(port, SIO_CHAR_XON);
            port->xon_rcv = true;
        } else if (!state && port->xon_rcv) {
            serial_send_ch_force(port, SIO_CHAR_XOFF);
            port->xon_rcv = false;
        }
    }
}

/* Drain remaining input after the main exchange loop stops. */
static sio_exit_code serial_flush(sio_port *port) {
    uint16_t loop_count = 0;

    for (;;) {
        if (serial_check_ch_available(port)) {
            uint8_t ch;

            loop_count = 0;
            ch = port_in((uint8_t)(port->addr - 1));
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

/* Append one character to the ring buffer. */
bool serial_buffer_put_ch(sio_buffer *buffer, uint8_t ch) {
    if (buffer->count == buffer->size) {
        return false;
    }
    buffer->values[buffer->put_ptr++] = ch;
    buffer->count++;
    if (buffer->put_ptr == buffer->size) {
        buffer->put_ptr = 0;
    }
    return true;
}

/* Append a byte span to the ring buffer. */
bool serial_buffer_put(sio_buffer *buffer, uint16_t len, const uint8_t *values) {
    uint16_t i;

    for (i = 0; i < len; i++) {
        if (!serial_buffer_put_ch(buffer, values[i])) {
            return false;
        }
    }
    return true;
}

/* Append a zero-terminated string to the ring buffer. */
bool serial_buffer_put_str(sio_buffer *buffer, const uint8_t *str) {
    const uint8_t *ptr;

    for (ptr = str; *ptr != 0; ptr++) {
        if (!serial_buffer_put_ch(buffer, *ptr)) {
            return false;
        }
    }
    return true;
}

/* Remove and return one byte from the ring buffer. */
uint8_t serial_buffer_get_ch(sio_buffer *buffer) {
    uint8_t ch;

    if (buffer->count == 0) {
        return 0;
    }
    ch = buffer->values[buffer->get_ptr++];
    buffer->count--;
    if (buffer->get_ptr == buffer->size) {
        buffer->get_ptr = 0;
    }
    return ch;
}

/* Peek a byte at an offset from the current read position. */
uint8_t serial_buffer_peek(sio_buffer *buffer, uint16_t idx) {
    if (buffer->count <= idx) {
        return 0;
    }
    idx += buffer->get_ptr;
    idx %= buffer->size;
    return buffer->values[idx];
}

/* Return true when the ring buffer holds no bytes. */
bool serial_buffer_empty(sio_buffer *buffer) {
    return buffer->count == 0;
}

/* Drain the whole ring buffer into caller-supplied storage. */
uint16_t serial_buffer_get(sio_buffer *buffer, uint8_t *dest) {
    uint8_t *p = dest;
    uint16_t count = buffer->count;

    while (!serial_buffer_empty(buffer)) {
        *(p++) = serial_buffer_get_ch(buffer);
    }
    return count;
}

/* Initialize one SIO channel and allocate its input/output buffers. */
sio_port *serial_init_ex(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity,
    sio_flow_control flow_control, uint16_t out_buffer_sz,
    uint16_t in_buffer_sz, uint16_t in_buffer_ext, uint16_t no_activity_thr) {
    sio_port *port;
    uint8_t i;

    for (i = 1; i < sio_init_str[0] + 1; i++) {
        uint8_t val = sio_init_str[i];
        if (i == 4) {
            val = (uint8_t)(bauds | stop_bits | parity);
        } else if (i == 8) {
            val = (mode == SIO_MODE_POLLING) ? 0x04 : 0x1C;
        } else if (i == 10) {
            val = (uint8_t)(data_bits | 1);
        }
        port_out(port_addr, val);
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
    port->wr5 = sio_init_str[6];
    port->flow_control = flow_control;
    port->xon_send = true;
    port->xon_rcv = true;
    return port;
}

/* Initialize one SIO channel with library default buffer sizes. */
sio_port *serial_init(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity,
    sio_flow_control flow_control) {
    return serial_init_ex(port_addr, mode, bauds, data_bits, stop_bits, parity,
        flow_control, 512, 128, 64, 100);
}

/* Read the CTS input from RR0. */
bool serial_check_cts(sio_port *port) {
    return (port_in(port->addr) & Z80SIO_RR0_CTS) != 0;
}

/* Drive RTS through WR5 while preserving the rest of the cached register value. */
void serial_set_rts(sio_port *port, bool state) {
    if (state && (port->wr5 & 2) == 0) {
        port_out(port->addr, 5);
        port->wr5 = (uint8_t)(port->wr5 | 2);
        port_out(port->addr, port->wr5);
    } else if (!state && (port->wr5 & 2) != 0) {
        port_out(port->addr, 5);
        port->wr5 = (uint8_t)(port->wr5 - 2);
        port_out(port->addr, port->wr5);
    }
}

/* Send queued output until flow control or buffer state stops progress. */
bool serial_send(sio_port *port) {
    while (serial_check_able_to_send(port) && !serial_buffer_empty(&port->buffer_out)) {
        while (!serial_check_tx_buffer_empty(port)) {
        }
        port_out((uint8_t)(port->addr - 1), serial_buffer_get_ch(&port->buffer_out));
    }
    return serial_buffer_empty(&port->buffer_out);
}

/* Non-blocking exchange loop with optional flow control and input buffering. */
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
                port_out((uint8_t)(port->addr - 1), serial_buffer_get_ch(&port->buffer_out));
            }
        }

        if (serial_check_ch_available(port)) {
            loop_count = 0;
            ch = port_in((uint8_t)(port->addr - 1));
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

/* Release all dynamically allocated storage associated with a port. */
void serial_done(sio_port *port) {
    free(port->buffer_in.values);
    free(port->buffer_out.values);
    free(port);
}
