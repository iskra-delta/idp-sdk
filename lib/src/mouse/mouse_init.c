/*
 * init.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include <stdlib.h>

#include "common.h"

void _mouse_logi_purge(mouse_t *mouse);

mouse_t *mouse_init(mouse_type_t type) {
    mouse_t *mouse;
    sio_bauds bauds = SIO_BAUDS_2400;
    sio_data_bits data_bits = SIO_DATA_BITS_7;
    sio_stop_bits stop_bits = SIO_STOP_BITS_1;
    sio_parity parity = SIO_PARITY_NONE;

    if (type == MOUSE_MOUSESYSTEMS) {
        data_bits = SIO_DATA_BITS_8;
        stop_bits = SIO_STOP_BITS_2;
    }

    mouse = calloc(1, sizeof(mouse_t));
    if (!mouse) {
        return NULL;
    }

    mouse->serial = serial_init_ex(
        SIO_PORT_LPT,
        SIO_MODE_POLLING,
        bauds,
        data_bits,
        stop_bits,
        parity,
        SIO_FLOW_CONTROL_NONE,
        16,
        64,
        16,
        1
    );
    if (!mouse->serial) {
        free(mouse);
        return NULL;
    }

    mouse->type = type;
    serial_set_dtr(mouse->serial, true);
    serial_set_rts(mouse->serial, true);
    mouse_reset(mouse);
    if (type == MOUSE_GENIUS_C7) {
        _mouse_logi_purge(mouse);
    }
    return mouse;
}
