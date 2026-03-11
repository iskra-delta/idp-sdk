#ifndef LIBPARTNER_CONIO_COMMON_H
#define LIBPARTNER_CONIO_COMMON_H

#include <stdint.h>

#include <partner/conio.h>
#include <partner/hw/partner/avdc.h>
#include <partner/hw/partner/kbd.h>

extern struct text_info _ti;

uint8_t conio_setup_width(void);

#endif
