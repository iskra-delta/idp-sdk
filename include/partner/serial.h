/*
 * serial.h
 *
 * Public Partner serial services.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#ifndef __PARTNER_SERIAL_H__
#define __PARTNER_SERIAL_H__

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    SIO_FLOW_CONTROL_RTSCTS,
    SIO_FLOW_CONTROL_XONXOFF,
    SIO_FLOW_CONTROL_NONE
} sio_flow_control;

typedef enum {
    SIO_BAUDS_153600 = 0,
    SIO_BAUDS_9600   = 64,
    SIO_BAUDS_4800   = 128,
    SIO_BAUDS_2400   = 128 | 64
} sio_bauds;

typedef enum {
    SIO_STOP_BITS_1 = 4,
    SIO_STOP_BITS_2 = 8 | 4
} sio_stop_bits;

typedef enum {
    SIO_PARITY_ODD  = 1,
    SIO_PARITY_EVEN = 2 | 1,
    SIO_PARITY_NONE = 0
} sio_parity;

typedef enum {
    SIO_DATA_BITS_5 = 0,
    SIO_DATA_BITS_6 = 128,
    SIO_DATA_BITS_7 = 64,
    SIO_DATA_BITS_8 = 128 | 64
} sio_data_bits;

typedef enum {
    SIO_MODE_POLLING
} sio_mode;

typedef enum {
    SIO_EXIT_CODE_NO_ACTIVITY,
    SIO_EXIT_CODE_BUFFER_FULL,
    SIO_EXIT_CODE_BUFFER_OVERFLOW
} sio_exit_code;

typedef enum {
    SIO_PORT_CRT,
    SIO_PORT_LPT,
    SIO_PORT_VAX,
    SIO_PORT_MOD
} sio_port_addr;

typedef struct {
    uint8_t *values;
    uint16_t put_ptr;
    uint16_t get_ptr;
    uint16_t count;
    uint16_t size;
} sio_buffer;

typedef struct {
    sio_buffer buffer_in;
    sio_buffer buffer_out;
    uint16_t no_activity_thr;
    uint16_t in_buffer_ext;
    uint8_t wr5;
    sio_port_addr addr;
    sio_flow_control flow_control;
    bool xon_send;
    bool xon_rcv;
} sio_port;

/* Initialize a serial port using default buffer sizing. */
extern sio_port *serial_init(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity,
    sio_flow_control flow_control);

/* Initialize a serial port with explicit buffer and timeout settings. */
extern sio_port *serial_init_ex(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity,
    sio_flow_control flow_control, uint16_t out_buffer_sz,
    uint16_t in_buffer_sz, uint16_t in_buffer_ext, uint16_t no_activity_thr);

/* Append a byte range to the circular buffer. */
extern bool serial_buffer_put(sio_buffer *buffer, uint16_t len, const uint8_t *values);

/* Append one byte to the circular buffer. */
extern bool serial_buffer_put_ch(sio_buffer *buffer, uint8_t ch);

/* Append a zero-terminated byte string to the circular buffer. */
extern bool serial_buffer_put_str(sio_buffer *buffer, const uint8_t *str);

/* Return whether the circular buffer currently holds no data. */
extern bool serial_buffer_empty(sio_buffer *buffer);

/* Remove and return one byte from the circular buffer. */
extern uint8_t serial_buffer_get_ch(sio_buffer *buffer);

/* Read one byte from the circular buffer without removing it. */
extern uint8_t serial_buffer_peek(sio_buffer *buffer, uint16_t idx);

/* Remove buffered data into the destination array and return the count. */
extern uint16_t serial_buffer_get(sio_buffer *buffer, uint8_t *dest);

/* Run one polling exchange cycle for receive and transmit processing. */
extern sio_exit_code serial_exchange(sio_port *port);

/* Flush pending transmit data to the serial device. */
extern bool serial_send(sio_port *port);

/* Assert or deassert RTS on the selected serial port. */
extern void serial_set_rts(sio_port *port, bool state);

/* Assert or deassert DTR on the selected serial port. */
extern void serial_set_dtr(sio_port *port, bool state);

/* Read the current CTS state from the selected serial port. */
extern bool serial_check_cts(sio_port *port);

/* Release all resources associated with the serial port. */
extern void serial_done(sio_port *port);

#endif /* __PARTNER_SERIAL_H__ */
