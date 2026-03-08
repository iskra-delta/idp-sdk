/*
 * serial.h
 *
 * Partner serial services and Z80 SIO port map.
 *
 * NOTES
 *  - Partner exposes two SIO devices.
 *  - SIO 1 is used for keyboard and printer.
 *  - SIO 2 is used for host / VAX communication.
 *  - On Partner, bit 0 selects data vs control and bit 1 selects
 *    channel A vs B within each SIO port block.
 *  - Port 0xE4 decodes like 0xE0 in the emulator address logic and
 *    is treated here as an alias of SIO 2 channel A data.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#ifndef __PARTNER_SERIAL_H__
#define __PARTNER_SERIAL_H__

#include <stdbool.h>
#include <stdint.h>

/* --- SIO 1: keyboard / printer ------------------------------------------ */
/* 0xD8 - Channel A data register */
#define Z80SIO1_DATA_A          0xD8
/* 0xD9 - Channel A control / status register */
#define Z80SIO1_CTRL_A          0xD9
/* 0xDA - Channel B data register */
#define Z80SIO1_DATA_B          0xDA
/* 0xDB - Channel B control / status register */
#define Z80SIO1_CTRL_B          0xDB

/* --- SIO 2: host / VAX --------------------------------------------------- */
/* 0xE0 - Channel A data register */
#define Z80SIO2_DATA_A          0xE0
/* 0xE1 - Channel A control / status register */
#define Z80SIO2_CTRL_A          0xE1
/* 0xE2 - Channel B data register */
#define Z80SIO2_DATA_B          0xE2
/* 0xE3 - Channel B control / status register */
#define Z80SIO2_CTRL_B          0xE3
/* 0xE4 - Alias of channel A data in current Partner decoding */
#define Z80SIO2_DATA_A_ALIAS    0xE4

/* --- RR0 / status bits commonly used for polling ------------------------ */
/* bit 0 - receive character available */
#define Z80SIO_RR0_RX_AVAIL     0x01
/* bit 2 - transmit buffer empty / ready */
#define Z80SIO_RR0_TX_EMPTY     0x04
/* bit 3 - data carrier detect */
#define Z80SIO_RR0_DCD          0x08
/* bit 4 - sync / hunt status */
#define Z80SIO_RR0_SYNC_HUNT    0x10
/* bit 5 - clear to send */
#define Z80SIO_RR0_CTS          0x20
/* bit 6 - transmit underrun / end of message */
#define Z80SIO_RR0_TX_UNDERRUN  0x40
/* bit 7 - break detected / abort */
#define Z80SIO_RR0_BREAK_ABORT  0x80

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
    SIO_PORT_CRT = Z80SIO1_CTRL_A,
    SIO_PORT_LPT = Z80SIO1_CTRL_B,
    SIO_PORT_VAX = Z80SIO2_CTRL_A,
    SIO_PORT_MOD = Z80SIO2_CTRL_B
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

/* Initialize a port with library default buffer sizes. */
sio_port *serial_init(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity,
    sio_flow_control flow_control);

/* Initialize a port with caller-supplied buffer sizes and thresholds. */
sio_port *serial_init_ex(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity,
    sio_flow_control flow_control, uint16_t out_buffer_sz,
    uint16_t in_buffer_sz, uint16_t in_buffer_ext, uint16_t no_activity_thr);

/* Append a byte span to a buffer. */
bool serial_buffer_put(sio_buffer *buffer, uint16_t len, const uint8_t *values);
/* Append one byte to a buffer. */
bool serial_buffer_put_ch(sio_buffer *buffer, uint8_t ch);
/* Append a zero-terminated string to a buffer. */
bool serial_buffer_put_str(sio_buffer *buffer, const uint8_t *str);
/* Return true when the buffer is empty. */
bool serial_buffer_empty(sio_buffer *buffer);
/* Remove one byte from a buffer. */
uint8_t serial_buffer_get_ch(sio_buffer *buffer);
/* Peek a byte at an offset from the current read position. */
uint8_t serial_buffer_peek(sio_buffer *buffer, uint16_t idx);
/* Drain the whole buffer to destination memory and return copied length. */
uint16_t serial_buffer_get(sio_buffer *buffer, uint8_t *dest);

/* Run one non-blocking send/receive exchange cycle. */
sio_exit_code serial_exchange(sio_port *port);
/* Send queued output bytes until blocked or empty. */
bool serial_send(sio_port *port);

/* Set or clear RTS for the selected port. */
void serial_set_rts(sio_port *port, bool state);
/* Read CTS state for the selected port. */
bool serial_check_cts(sio_port *port);

/* Free all resources associated with a port. */
void serial_done(sio_port *port);

#endif /* __PARTNER_SERIAL_H__ */
