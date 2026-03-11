#ifndef LIBPARTNER_CONIO_COMMON_H
#define LIBPARTNER_CONIO_COMMON_H

#include <stdbool.h>
#include <stdint.h>

#include <hw/kbd.h>
#include <hw/scn2674.h>
#include <partner/conio.h>

extern struct text_info _ti;
extern bool _conio_kbhit_use_bdos;

void _conio_init(void);
void _conio_exit(void);
void _serial_port_out(uint8_t port, uint8_t value);
void scn2674_puts_burst(const char *s, uint8_t len, unsigned char attr);

#endif
