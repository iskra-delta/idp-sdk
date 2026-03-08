/*
 * mouse.h
 *
 * Generic streaming serial mouse support for Partner.
 *
 * NOTES:
 *  - This layer supports classic streaming serial mouse families.
 *  - The caller selects a protocol explicitly in mouse_init().
 *  - Decoded state is normalized to dx/dy/button fields.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2026 Tomaz Stih
 *
 * 08.03.2026   tstih
 *
 */
#ifndef __PARTNER_MOUSE_H__
#define __PARTNER_MOUSE_H__

#include <stdbool.h>
#include <stdint.h>

#include <partner/hw/partner/serial.h>

typedef enum {
    MOUSE_MICROSOFT,
    MOUSE_GENIUS_C7,
    MOUSE_MOUSESYSTEMS
} mouse_type_t;

/* Backward-compatible alias for older code using the earlier name. */
#define MOUSE_LOGITECH MOUSE_GENIUS_C7

enum {
    MOUSE_BUTTON_LEFT   = 0x01,
    MOUSE_BUTTON_MIDDLE = 0x02,
    MOUSE_BUTTON_RIGHT  = 0x04
};

typedef struct mouse_state_s {
    mouse_type_t type;
    sio_port *serial;
    int16_t x;
    int16_t y;
    int16_t dx;
    int16_t dy;
    uint8_t buttons;
    uint8_t packet[5];
    uint8_t count;
    bool synced;
} mouse_t;

/* Initialize a streaming serial mouse using the selected protocol. */
mouse_t *mouse_init(mouse_type_t type);

/* Reset decoder state and clear accumulated motion. */
void mouse_reset(mouse_t *mouse);

/* Poll the serial port, decode any pending packets, and update state. */
void mouse_poll(mouse_t *mouse);

/* Free all resources associated with the mouse. */
void mouse_done(mouse_t *mouse);

#endif /* __PARTNER_MOUSE_H__ */
