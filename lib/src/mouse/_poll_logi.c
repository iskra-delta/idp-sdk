/*
 * _poll_logi.c
 *
 * Partner LOGI mouse polling.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 */
#include "common.h"

#define MOUSE_LOGI_INIT_CMD   99u
#define MOUSE_LOGI_POLL_CMD   80u
#define MOUSE_LOGI_INIT_LEN   60u
#define MOUSE_LOGI_REPLY_LEN  5u
#define MOUSE_LOGI_MAX_POLLS  8u

static int16_t mouse_logi_decode_delta(uint8_t lo, uint8_t hi) {
    uint16_t value = (uint16_t)(lo & 0x3Fu) | (uint16_t)((uint16_t)(hi & 0x3Fu) << 6);

    if ((value & 0x0800u) != 0) {
        value |= 0xF000u;
    }
    return (int16_t)value;
}

static void mouse_logi_exchange(sio_port *port) {
    serial_buffer_put_ch(&port->buffer_out, MOUSE_LOGI_POLL_CMD);
    serial_send(port);
    (void)serial_exchange(port);
}

void _mouse_poll_logi(mouse_t *mouse) {
    uint8_t packet[MOUSE_LOGI_REPLY_LEN];
    uint8_t buttons = 0;
    int16_t dx;
    int16_t dy;
    uint8_t i;
    uint8_t polls = 0;

    mouse_logi_exchange(mouse->serial);
    while (mouse->serial->buffer_in.count < MOUSE_LOGI_REPLY_LEN &&
        polls < MOUSE_LOGI_MAX_POLLS) {
        if (serial_exchange(mouse->serial) == SIO_EXIT_CODE_NO_ACTIVITY) {
            polls++;
        }
    }
    if (mouse->serial->buffer_in.count < MOUSE_LOGI_REPLY_LEN) {
        while (!serial_buffer_empty(&mouse->serial->buffer_in)) {
            (void)serial_buffer_get_ch(&mouse->serial->buffer_in);
        }
        return;
    }

    for (i = 0; i < MOUSE_LOGI_REPLY_LEN; i++) {
        packet[i] = serial_buffer_get_ch(&mouse->serial->buffer_in);
    }
    while (!serial_buffer_empty(&mouse->serial->buffer_in)) {
        (void)serial_buffer_get_ch(&mouse->serial->buffer_in);
    }

    if ((packet[0] & 0x10u) != 0) {
        buttons |= MOUSE_BUTTON_LEFT;
    }
    if ((packet[0] & 0x08u) != 0) {
        buttons |= MOUSE_BUTTON_MIDDLE;
    }
    if ((packet[0] & 0x04u) != 0) {
        buttons |= MOUSE_BUTTON_RIGHT;
    }

    dx = mouse_logi_decode_delta(packet[1], packet[2]);
    dy = mouse_logi_decode_delta(packet[3], packet[4]);

    _mouse_apply_packet(mouse, dx, -dy, buttons);
}

void _mouse_logi_purge(mouse_t *mouse) {
    uint8_t remaining = MOUSE_LOGI_INIT_LEN;

    serial_buffer_put_ch(&mouse->serial->buffer_out, MOUSE_LOGI_INIT_CMD);
    serial_send(mouse->serial);

    while (remaining > 0) {
        (void)serial_exchange(mouse->serial);
        while (remaining > 0 && !serial_buffer_empty(&mouse->serial->buffer_in)) {
            (void)serial_buffer_get_ch(&mouse->serial->buffer_in);
            remaining--;
        }
        if (mouse->serial->buffer_in.count == 0 &&
            serial_exchange(mouse->serial) == SIO_EXIT_CODE_NO_ACTIVITY) {
            break;
        }
    }

    while (!serial_buffer_empty(&mouse->serial->buffer_in)) {
        (void)serial_buffer_get_ch(&mouse->serial->buffer_in);
    }
}
