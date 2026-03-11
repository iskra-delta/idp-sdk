#ifndef LIBPARTNER_MOUSE_COMMON_H
#define LIBPARTNER_MOUSE_COMMON_H

#include <partner/mouse.h>

void _mouse_reset_decoder(mouse_t *mouse);
void _mouse_apply_packet(mouse_t *mouse, int8_t dx, int8_t dy, uint8_t buttons);
void _mouse_feed_microsoft(mouse_t *mouse, uint8_t b);
void _mouse_feed_mousesystems(mouse_t *mouse, uint8_t b);

#endif
