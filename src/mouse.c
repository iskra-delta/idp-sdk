/*
 * mouse.c
 *
 * Generic streaming serial mouse support for Partner.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#include <stdlib.h>

#include <partner/mouse.h>

/* Reset transient decoder state without touching the serial port object. */
static void mouse_reset_decoder(mouse_t *mouse) {
    mouse->x = 0;
    mouse->y = 0;
    mouse->dx = 0;
    mouse->dy = 0;
    mouse->buttons = 0;
    mouse->count = 0;
    mouse->synced = false;
}

/* Apply one decoded relative movement packet to the public state. */
static void mouse_apply_packet(mouse_t *mouse, int8_t dx, int8_t dy, uint8_t buttons) {
    mouse->dx += dx;
    mouse->dy += dy;
    mouse->x += dx;
    mouse->y += dy;
    mouse->buttons = buttons;
}

/* Feed one Microsoft-compatible byte into the decoder. */
static void mouse_feed_microsoft(mouse_t *mouse, uint8_t b) {
    uint8_t buttons;
    int8_t dx;
    int8_t dy;

    if (mouse->count == 0) {
        if ((b & 0x40) == 0) {
            return;
        }
        mouse->packet[mouse->count++] = b;
        mouse->synced = true;
        return;
    }

    if ((b & 0x40) != 0) {
        mouse->packet[0] = b;
        mouse->count = 1;
        mouse->synced = true;
        return;
    }

    if (mouse->count < 3) {
        mouse->packet[mouse->count++] = b;
    } else if (mouse->type == MOUSE_GENIUS_C7) {
        mouse->buttons &= (uint8_t)~MOUSE_BUTTON_MIDDLE;
        if ((b & 0x20) != 0) {
            mouse->buttons |= MOUSE_BUTTON_MIDDLE;
        }
        mouse->count = 0;
        mouse->synced = false;
        return;
    } else {
        mouse->count = 0;
        mouse->synced = false;
        return;
    }

    if (mouse->count != 3) {
        return;
    }

    buttons = 0;
    if ((mouse->packet[0] & 0x20) != 0) {
        buttons |= MOUSE_BUTTON_LEFT;
    }
    if ((mouse->packet[0] & 0x10) != 0) {
        buttons |= MOUSE_BUTTON_RIGHT;
    }
    if (mouse->type == MOUSE_GENIUS_C7) {
        buttons |= (mouse->buttons & MOUSE_BUTTON_MIDDLE);
    }

    dx = (int8_t)(((mouse->packet[0] & 0x03) << 6) | (mouse->packet[1] & 0x3F));
    dy = (int8_t)(((mouse->packet[0] & 0x0C) << 4) | (mouse->packet[2] & 0x3F));

    mouse_apply_packet(mouse, dx, dy, buttons);
    mouse->count = (mouse->type == MOUSE_GENIUS_C7) ? 3 : 0;
    mouse->synced = (mouse->type == MOUSE_GENIUS_C7);
}

/* Feed one Mouse Systems byte into the decoder. */
static void mouse_feed_mousesystems(mouse_t *mouse, uint8_t b) {
    uint8_t buttons;
    int8_t dx;
    int8_t dy;

    if (mouse->count == 0) {
        if ((b & 0xF8) != 0x80) {
            return;
        }
        mouse->packet[mouse->count++] = b;
        mouse->synced = true;
        return;
    }

    if ((b & 0xF8) == 0x80) {
        mouse->packet[0] = b;
        mouse->count = 1;
        mouse->synced = true;
        return;
    }

    if (mouse->count < 5) {
        mouse->packet[mouse->count++] = b;
    }

    if (mouse->count != 5) {
        return;
    }

    buttons = 0;
    if ((mouse->packet[0] & 0x04) == 0) {
        buttons |= MOUSE_BUTTON_LEFT;
    }
    if ((mouse->packet[0] & 0x02) == 0) {
        buttons |= MOUSE_BUTTON_MIDDLE;
    }
    if ((mouse->packet[0] & 0x01) == 0) {
        buttons |= MOUSE_BUTTON_RIGHT;
    }

    dx = (int8_t)((int8_t)mouse->packet[1] + (int8_t)mouse->packet[3]);
    dy = (int8_t)(-((int8_t)mouse->packet[2] + (int8_t)mouse->packet[4]));

    mouse_apply_packet(mouse, dx, dy, buttons);
    mouse->count = 0;
    mouse->synced = false;
}

/* Initialize a streaming serial mouse using the selected protocol. */
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
    mouse_reset(mouse);
    return mouse;
}

/* Reset decoder state and clear accumulated motion. */
void mouse_reset(mouse_t *mouse) {
    mouse_reset_decoder(mouse);
}

/* Poll the serial port, decode any pending packets, and update state. */
void mouse_poll(mouse_t *mouse) {
    uint8_t b;

    mouse->dx = 0;
    mouse->dy = 0;

    (void)serial_exchange(mouse->serial);
    while (!serial_buffer_empty(&mouse->serial->buffer_in)) {
        b = serial_buffer_get_ch(&mouse->serial->buffer_in);
        switch (mouse->type) {
        case MOUSE_MICROSOFT:
        case MOUSE_GENIUS_C7:
            mouse_feed_microsoft(mouse, b);
            break;
        case MOUSE_MOUSESYSTEMS:
            mouse_feed_mousesystems(mouse, b);
            break;
        }
    }
}

/* Free all resources associated with the mouse. */
void mouse_done(mouse_t *mouse) {
    if (!mouse) {
        return;
    }
    if (mouse->serial) {
        serial_done(mouse->serial);
    }
    free(mouse);
}
