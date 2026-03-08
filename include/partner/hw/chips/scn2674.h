/*
 * scn2674.h
 *
 * Raw SCN2674 controller access declarations.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2022 Tomaz Stih
 *
 * 05.05.2022   tstih
 *
 */
#ifndef __PARTNER_CHIPS_SCN2674_H__
#define __PARTNER_CHIPS_SCN2674_H__
#include <stdint.h>

/* poll the controller until it becomes ready */
extern void scn2674_wait_rdy(void);

/* set cursor address */
extern void scn2674_set_cursor(uint16_t addr);

/* get cursor address */
extern uint16_t scn2674_get_cursor(void);

/* set pointer address */
extern void scn2674_set_pointer(uint16_t addr);

/* enable text cursor */
extern void scn2674_cursor_on(void);

/* disable text cursor */
extern void scn2674_cursor_off(void);

#endif /* __PARTNER_CHIPS_SCN2674_H__ */
