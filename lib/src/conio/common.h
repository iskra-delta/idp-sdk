#ifndef LIBPARTNER_CONIO_COMMON_H
#define LIBPARTNER_CONIO_COMMON_H

#include <stdint.h>

#include <hw/kbd.h>
#include <hw/scn2674.h>
#include <partner/conio.h>

extern struct text_info _ti;

uint8_t _conio_setup_width(void);

#endif
