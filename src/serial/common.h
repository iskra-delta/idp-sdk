#ifndef LIBPARTNER_SERIAL_COMMON_H
#define LIBPARTNER_SERIAL_COMMON_H

#include <stdbool.h>
#include <stdint.h>

#include <partner/hw/chips/z80.h>
#include <partner/hw/partner/serial.h>

#define SIO_CHAR_XON  17
#define SIO_CHAR_XOFF 19

void serial_buffer_alloc_internal(sio_buffer *buffer, uint16_t size);
bool serial_check_tx_buffer_empty(sio_port *port);
bool serial_check_ch_available(sio_port *port);
void serial_send_ch_force(sio_port *port, uint8_t ch);
bool serial_check_able_to_send(sio_port *port);
void serial_set_able_to_rcv(sio_port *port, bool state);
sio_exit_code serial_flush(sio_port *port);
uint8_t serial_init_wr5_default(void);
uint8_t serial_init_value(uint8_t idx, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity);

#endif
