# libpartner

`libpartner` is a static library for the Iskra Delta Partner.

It exposes three layers:

- top-level convenience APIs in `include/partner/`
- Partner-specific hardware APIs in `include/partner/hw/partner/`
- raw chip declarations in `include/partner/hw/chips/`

Build output:

- library: `bin/libpartner.lib`
- exported headers: `bin/include/partner/...`
- sample programs: `bin/samples/*.com`
- sample disk image: `bin/samples.img`

## Build

Build the library:

```sh
make
```

Build sample `.com` programs and package them into a CP/M disk image:

```sh
make samples
```

Typical compile line for your own program:

```sh
sdcc -mz80 -Ibin/include myprog.c bin/libpartner.lib
```

## Public Headers

- `partner.h`
- `partner/bcd.h`
- `partner/conio.h`
- `partner/mouse.h`
- `partner/port.h`
- `partner/timer.h`
- `partner/hw/partner/avdc.h`
- `partner/hw/partner/kbd.h`
- `partner/hw/partner/nvram.h`
- `partner/hw/partner/rtc.h`
- `partner/hw/partner/serial.h`
- `partner/hw/chips/scn2674.h`
- `partner/hw/chips/mm58167a.h`
- `partner/hw/chips/z80sio.h`

## API Reference

<details>
<summary><code>partner.h</code></summary>

Umbrella include for the main public API.

Includes:

- `partner/bcd.h`
- `partner/conio.h`
- `partner/mouse.h`
- `partner/hw/partner/nvram.h`
- `partner/hw/partner/serial.h`
- `partner/timer.h`

Example:

```c
#include <partner.h>
```

</details>

<details>
<summary><code>partner/bcd.h</code></summary>

8-bit packed BCD conversion helpers.

`uint8_t bin2bcd(uint8_t bin);`

```c
#include <partner/bcd.h>

uint8_t bcd = bin2bcd(45); /* 0x45 */
```

`uint8_t bcd2bin(uint8_t bcd);`

```c
#include <partner/bcd.h>

uint8_t value = bcd2bin(0x59); /* 59 */
```

</details>

<details>
<summary><code>partner/conio.h</code></summary>

Fast text console helpers built on the Partner AVDC.

Attributes:

- `AT_NORMAL`
- `AT_BLINK`
- `AT_UNDERLINE`
- `AT_HIGHLIGHT`
- `AT_REVERSE`

Cursor modes:

- `NOCURSOR`
- `NORMALCURSOR`

`int kbhit(void);`

```c
int ch = kbhit();
if (ch) putch(ch);
```

`void gotoxy(int x, int y);`

```c
gotoxy(10, 5);
```

`void clrscr(void);`

```c
clrscr();
```

`void setattr(unsigned char attr);`

```c
setattr(AT_HIGHLIGHT | AT_BLINK);
```

`void gettextinfo(struct text_info *r);`

```c
struct text_info ti;
gettextinfo(&ti);
```

`int putch(int c);`

```c
putch('A');
```

`void rdchat(char *c, unsigned char *attr);`

```c
char ch;
unsigned char attr;
rdchat(&ch, &attr);
```

`int cputs(const char *str);`

```c
cputs("Partner");
```

`int wherex(void);`

```c
int x = wherex();
```

`int wherey(void);`

```c
int y = wherey();
```

`void setcursortype(int cur_t);`

```c
setcursortype(NOCURSOR);
```

</details>

<details>
<summary><code>partner/mouse.h</code></summary>

Generic streaming serial mouse support.

Supported protocols:

- `MOUSE_MICROSOFT`
- `MOUSE_GENIUS_C7`
- `MOUSE_MOUSESYSTEMS`

Button bits:

- `MOUSE_BUTTON_LEFT`
- `MOUSE_BUTTON_MIDDLE`
- `MOUSE_BUTTON_RIGHT`

Type:

- `mouse_t`

`mouse_t *mouse_init(mouse_type_t type);`

```c
mouse_t *mouse = mouse_init(MOUSE_GENIUS_C7);
```

`void mouse_reset(mouse_t *mouse);`

```c
mouse_reset(mouse);
```

`void mouse_poll(mouse_t *mouse);`

```c
mouse_poll(mouse);
```

`void mouse_done(mouse_t *mouse);`

```c
mouse_done(mouse);
```

</details>

<details>
<summary><code>partner/port.h</code></summary>

Generic Z80 I/O port access helpers.

`uint8_t port_in(uint8_t port);`

```c
#include <partner/port.h>

uint8_t status = port_in(0xD9);
```

`void port_out(uint8_t port, uint8_t value);`

```c
#include <partner/port.h>

port_out(0xD8, 'A');
```

</details>

<details>
<summary><code>partner/timer.h</code></summary>

Short-interval timer helpers built on the RTC.

`uint16_t timer_ms(void);`

```c
uint16_t t0 = timer_ms();
```

`int16_t timer(void);`

```c
int16_t t = timer();
```

`int16_t timer_diff(uint16_t timer_start, uint16_t timer_offset);`

```c
uint16_t start = timer();
int16_t dt = timer_diff(start, 0);
```

</details>

<details>
<summary><code>partner/hw/partner/nvram.h</code></summary>

Partner non-volatile terminal setup storage backed by MM58167A.

Type:

- `nvram_settings_t`

`void nvram_get_settings(nvram_settings_t *settings);`

```c
nvram_settings_t settings;
nvram_get_settings(&settings);
```

`void nvram_set_settings(const nvram_settings_t *settings);`

```c
nvram_settings_t settings;
nvram_get_settings(&settings);
settings.width = 132;
nvram_set_settings(&settings);
```

</details>

<details>
<summary><code>partner/hw/partner/avdc.h</code></summary>

Partner AVDC services and Partner-specific SCN2674 register map.

Common constants:

- `SCN2674_CHR`
- `SCN2674_AT`
- `SCN2674_CMD`
- `SCN2674_STS`
- `SCN2674_AT_BLINK`
- `SCN2674_AT_UNDERLINE`
- `SCN2674_AT_HIGHLIGHT`
- `SCN2674_AT_REVERSE`

`void avdc_wait_mem_acc(void);`

```c
avdc_wait_mem_acc();
```

`uint16_t avdc_cursor_addr(void);`

```c
uint16_t addr = avdc_cursor_addr();
```

`void avdc_cache_rows(void);`

```c
avdc_cache_rows();
```

`void avdc_invalidate_row_cache(void);`

```c
avdc_invalidate_row_cache();
```

`uint16_t avdc_rowptr(uint8_t row);`

```c
uint16_t row0 = avdc_rowptr(0);
```

`void avdc_cls(void);`

```c
avdc_cls();
```

`void avdc_show_cursor(void);`

```c
avdc_show_cursor();
```

`void avdc_hide_cursor(void);`

```c
avdc_hide_cursor();
```

`void avdc_xy(int x, int y);`

```c
avdc_xy(20, 10);
```

`void avdc_burst(const char *chars, uint8_t attr, uint8_t count);`

```c
static const char msg[] = "HELLO";
avdc_burst(msg, SCN2674_AT_HIGHLIGHT, 5);
```

`void avdc_putchar(char ch, unsigned char attr);`

```c
avdc_putchar('X', SCN2674_AT_NONE);
```

`void avdc_getchar(char *ch, unsigned char *attr);`

```c
char ch;
unsigned char attr;
avdc_getchar(&ch, &attr);
```

</details>

<details>
<summary><code>partner/hw/partner/kbd.h</code></summary>

Partner keyboard helpers on SIO 1 channel A.

Useful constants:

- `KBD_DATA`
- `KBD_STATUS`
- `KBD_STATUS_RX_READY`
- `KBD_STATUS_TX_READY`
- `KBD_CMD_BEEP`

`void kbd_wait_ready(void);`

```c
kbd_wait_ready();
```

`void kbd_beep(bool long_beep);`

```c
kbd_beep(false);
```

`char kbd_get_key(void);`

```c
char ch = kbd_get_key();
```

</details>

<details>
<summary><code>partner/hw/partner/rtc.h</code></summary>

Partner MM58167A RTC services and port map.

Useful constants:

- `MM58167A_THOUS_S`
- `MM58167A_HUNDR_S`
- `MM58167A_SECOND`
- `MM58167A_MINUTE`
- `MM58167A_HOUR`
- `MM58167A_WDAY`
- `MM58167A_MDAY`
- `MM58167A_MONTH`
- `MM58167A_YEAR`
- `MM58167A_GO`
- `MM58167A_RESET_NVRAM`

Type:

- `rtc_time_t`

`void rtc_reset(void);`

```c
rtc_reset();
```

`void rtc_reset_nvram(void);`

```c
rtc_reset_nvram();
```

`void rtc_get(rtc_time_t *t);`

```c
rtc_time_t now;
rtc_get(&now);
```

`void rtc_set(const rtc_time_t *t);`

```c
rtc_time_t t = { 0, 0, 30, 12, 1, 1, 1, 26 };
rtc_set(&t);
```

</details>

<details>
<summary><code>partner/hw/partner/serial.h</code></summary>

Partner serial services and Partner SIO port map.

Port constants:

- `Z80SIO1_DATA_A`, `Z80SIO1_CTRL_A`
- `Z80SIO1_DATA_B`, `Z80SIO1_CTRL_B`
- `Z80SIO2_DATA_A`, `Z80SIO2_CTRL_A`
- `Z80SIO2_DATA_B`, `Z80SIO2_CTRL_B`
- `Z80SIO_RR0_RX_AVAIL`
- `Z80SIO_RR0_TX_EMPTY`
- `Z80SIO_RR0_CTS`

Configuration enums:

- `sio_flow_control`
- `sio_bauds`
- `sio_stop_bits`
- `sio_parity`
- `sio_data_bits`
- `sio_mode`
- `sio_exit_code`
- `sio_port_addr`

Types:

- `sio_buffer`
- `sio_port`

`sio_port *serial_init(...);`

```c
sio_port *port = serial_init(
    SIO_PORT_LPT,
    SIO_MODE_POLLING,
    SIO_BAUDS_9600,
    SIO_DATA_BITS_8,
    SIO_STOP_BITS_1,
    SIO_PARITY_NONE,
    SIO_FLOW_CONTROL_NONE
);
```

`sio_port *serial_init_ex(...);`

```c
sio_port *port = serial_init_ex(
    SIO_PORT_LPT,
    SIO_MODE_POLLING,
    SIO_BAUDS_9600,
    SIO_DATA_BITS_8,
    SIO_STOP_BITS_1,
    SIO_PARITY_NONE,
    SIO_FLOW_CONTROL_NONE,
    512, 128, 64, 100
);
```

`bool serial_buffer_put(sio_buffer *buffer, uint16_t len, const uint8_t *values);`

```c
static const uint8_t msg[] = { 'O', 'K' };
serial_buffer_put(&port->buffer_out, 2, msg);
```

`bool serial_buffer_put_ch(sio_buffer *buffer, uint8_t ch);`

```c
serial_buffer_put_ch(&port->buffer_out, 'A');
```

`bool serial_buffer_put_str(sio_buffer *buffer, const uint8_t *str);`

```c
serial_buffer_put_str(&port->buffer_out, (const uint8_t *)"HELLO");
```

`bool serial_buffer_empty(sio_buffer *buffer);`

```c
if (serial_buffer_empty(&port->buffer_in)) {
}
```

`uint8_t serial_buffer_get_ch(sio_buffer *buffer);`

```c
uint8_t ch = serial_buffer_get_ch(&port->buffer_in);
```

`uint8_t serial_buffer_peek(sio_buffer *buffer, uint16_t idx);`

```c
uint8_t ch = serial_buffer_peek(&port->buffer_in, 0);
```

`uint16_t serial_buffer_get(sio_buffer *buffer, uint8_t *dest);`

```c
uint8_t buf[32];
uint16_t n = serial_buffer_get(&port->buffer_in, buf);
```

`sio_exit_code serial_exchange(sio_port *port);`

```c
sio_exit_code rc = serial_exchange(port);
```

`bool serial_send(sio_port *port);`

```c
serial_send(port);
```

`void serial_set_rts(sio_port *port, bool state);`

```c
serial_set_rts(port, true);
```

`bool serial_check_cts(sio_port *port);`

```c
if (serial_check_cts(port)) {
}
```

`void serial_done(sio_port *port);`

```c
serial_done(port);
```

</details>

<details>
<summary><code>partner/hw/chips/scn2674.h</code></summary>

Raw SCN2674 controller primitives.

`void scn2674_wait_rdy(void);`

```c
scn2674_wait_rdy();
```

`void scn2674_set_cursor(uint16_t addr);`

```c
scn2674_set_cursor(0x0200);
```

`uint16_t scn2674_get_cursor(void);`

```c
uint16_t addr = scn2674_get_cursor();
```

`void scn2674_set_pointer(uint16_t addr);`

```c
scn2674_set_pointer(0x0300);
```

`void scn2674_cursor_on(void);`

```c
scn2674_cursor_on();
```

`void scn2674_cursor_off(void);`

```c
scn2674_cursor_off();
```

</details>

<details>
<summary><code>partner/hw/chips/mm58167a.h</code></summary>

Chip-level placeholder for MM58167A.

Partner-specific bindings live in `partner/hw/partner/rtc.h`.

```c
#include <partner/hw/chips/mm58167a.h>
```

</details>

<details>
<summary><code>partner/hw/chips/z80sio.h</code></summary>

Chip-level placeholder for Z80 SIO.

Partner-specific bindings live in `partner/hw/partner/serial.h`.

```c
#include <partner/hw/chips/z80sio.h>
```

</details>

## Samples

Current samples:

- `samples/console.c`
- `samples/mouse.c`
- `samples/sysinfo.c`
- `samples/terminal.c`

Build them and create a CP/M disk image:

```sh
make samples
```

Outputs:

- `bin/samples/console.com`
- `bin/samples/mouse.com`
- `bin/samples/sysinfo.com`
- `bin/samples/terminal.com`
- `bin/samples.img`

## Notes

- Start with `partner.h` for applications.
- Use `partner/conio.h` for text-mode programs.
- Use `partner/mouse.h` for generic streaming serial mice.
- Use `partner/hw/partner/nvram.h` to read or change Partner setup values.
- Use `partner/hw/partner/serial.h` for Partner serial communication.
- Use `partner/port.h` only when you need direct raw I/O port access.
