/*
 * bcd.h
 *
 * 8-bit binary coded decimal conversions.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2021 Tomaz Stih
 *
 * 22.06.2021   tstih
 *
 */
#ifndef __PARTNER_BCD_H__
#define __PARTNER_BCD_H__

#include <stdint.h>

extern uint8_t bin2bcd(uint8_t bin);
extern uint8_t bcd2bin(uint8_t bcd);

#endif /* __PARTNER_BCD_H__ */
