#ifndef LIBPARTNER_MOUSE_COMMON_H
#define LIBPARTNER_MOUSE_COMMON_H

#include <partner/mouse.h>

void _mouse_reset_decoder(mouse_t *mouse);
void _mouse_apply_packet(mouse_t *mouse, int16_t dx, int16_t dy, uint8_t buttons);
void _mouse_feed_microsoft(mouse_t *mouse, uint8_t b);
void _mouse_feed_mousesystems(mouse_t *mouse, uint8_t b);
void _mouse_poll_logi(mouse_t *mouse);

#endif
