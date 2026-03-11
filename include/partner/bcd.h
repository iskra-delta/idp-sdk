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

/* Convert an 8-bit binary value to packed BCD. */
extern uint8_t bin2bcd(uint8_t bin);

/* Convert an 8-bit packed BCD value to binary. */
extern uint8_t bcd2bin(uint8_t bcd);

#endif /* __PARTNER_BCD_H__ */
