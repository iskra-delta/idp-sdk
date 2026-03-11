/*
 * done.c
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include <stdlib.h>

#include "common.h"

void serial_done(sio_port *port) {
    free(port->buffer_in.values);
    free(port->buffer_out.values);
    free(port);
}
