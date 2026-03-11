#ifndef LIBPARTNER_SERIAL_COMMON_H
#define LIBPARTNER_SERIAL_COMMON_H

#include <stdbool.h>
#include <stdint.h>

#include <hw/sio.h>
#include <partner/serial.h>

#define SIO_CHAR_XON  17
#define SIO_CHAR_XOFF 19

void _serial_buffer_alloc_internal(sio_buffer *buffer, uint16_t size);
bool _serial_check_tx_buffer_empty(sio_port *port);
bool _serial_check_ch_available(sio_port *port);
void _serial_send_ch_force(sio_port *port, uint8_t ch);
bool _serial_check_able_to_send(sio_port *port);
void _serial_set_able_to_rcv(sio_port *port, bool state);
sio_exit_code _serial_flush(sio_port *port);
uint8_t _serial_init_wr5_default(void);
uint8_t _serial_init_value(uint8_t idx, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity);
#define _serial_ctrl_port(port_addr) \
    ((port_addr) == SIO_PORT_CRT ? Z80SIO1_CTRL_A : \
    ((port_addr) == SIO_PORT_LPT ? Z80SIO1_CTRL_B : \
    ((port_addr) == SIO_PORT_VAX ? Z80SIO2_CTRL_A : Z80SIO2_CTRL_B)))

#define _serial_data_port(port_addr) \
    ((port_addr) == SIO_PORT_CRT ? Z80SIO1_DATA_A : \
    ((port_addr) == SIO_PORT_LPT ? Z80SIO1_DATA_B : \
    ((port_addr) == SIO_PORT_VAX ? Z80SIO2_DATA_A : Z80SIO2_DATA_B)))

uint8_t _serial_port_in(uint8_t port);
void _serial_port_out(uint8_t port, uint8_t value);

#endif
