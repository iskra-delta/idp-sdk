/*
 * init_params.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

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

uint8_t serial_init_wr5_default(void) {
    return sio_init_str[6];
}

uint8_t serial_init_value(uint8_t idx, sio_mode mode, sio_bauds bauds,
    sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity) {
    uint8_t val = sio_init_str[idx];

    if (idx == 4) {
        val = (uint8_t)(bauds | stop_bits | parity);
    } else if (idx == 8) {
        val = (mode == SIO_MODE_POLLING) ? 0x04 : 0x1C;
    } else if (idx == 10) {
        val = (uint8_t)(data_bits | 1);
    }

    return val;
}
