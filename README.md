# idp-sdk

Static SDK for the Iskra Delta Partner, built with SDCC Z80 and CP/M 3 runtime support.

The SDK ships:

- `libplatform.lib` for Partner-specific platform hooks required by `libcpm3-z80`
- `libsdk.lib` for console I/O, serial communication, mouse support, clock helpers, and debug helpers
- rebuilt copies of `libcpm3-z80`, `libsdcc-z80`, and `crt0cpm3-z80`
- public headers under `include/partner/`
- sample CP/M `.COM` programs under `samples/`

## Table of contents

- [Introduction](#introduction)
- [Repository layout](#repository-layout)
- [Build](#build)
- [Build outputs](#build-outputs)
- [Compiling your own program](#compiling-your-own-program)
- [Samples](#samples)
- [Public headers](#public-headers)
- [API reference](#api-reference)
- [partner/bcd.h](#partnerbcdh)
- [partner/clock.h](#partnerclockh)
- [partner/conio.h](#partnerconioh)
- [partner/debug.h](#partnerdebugh)
- [partner/mouse.h](#partnermouseh)
- [partner/serial.h](#partnerserialh)
- [partner/timer.h](#partnertimerh)

## Introduction

`idp-sdk` is an SDK for writing CP/M 3 programs for the Iskra Delta Partner.
It combines:

- Partner-specific SDK code from this repository
- `libcpm3-z80` rebuilt with `PLATFORM=PARTNER`
- `libsdcc-z80` rebuilt locally into the final `bin/` output

The public API is intentionally small. Raw hardware port maps are kept internal under `lib/include/hw/` and are not installed as part of the public SDK surface.

## Repository layout

| Path | Purpose |
|------|---------|
| `include/partner/` | Public SDK headers |
| `lib/src/` | SDK implementation sources |
| `lib/include/hw/` | Internal hardware maps and private low-level constants |
| `samples/` | Small example programs |
| `third_party/libcpm3-z80/` | Vendored CP/M 3 standard library source |
| `third_party/libsdcc-z80/` | Vendored SDCC support library source |
| `third_party/cpmdisk/` | Disk image tool used for packaging samples |
| `bin/` | Final libraries, CRT0, exported headers, and samples |
| `build/` | Intermediate build artifacts |

## Build

### Commands

| Command | Description |
|---------|-------------|
| `make` | Build the SDK libraries, CRT0, exported headers, and samples |
| `make build` | Build libraries, CRT0, and exported headers only |
| `make samples` | Build the SDK and package the sample `.COM` files into a disk image |
| `make cpmdisk` | Build the local `cpmdisk` binary |
| `make clean` | Remove `build/` and `bin/` |
| `make shell` | Open a shell in the Docker image used for the Z80 builds |

### Build model

- SDK and CP/M library builds run inside the `wischner/sdcc-z80` Docker image
- `cpmdisk` is compiled locally on the host machine
- third-party repositories are cloned into `third_party/` on demand and kept as a local cache

### Main variables

| Variable | Default | Description |
|----------|---------|-------------|
| `IMAGE` | `wischner/sdcc-z80` | Docker image used for Z80 compilation |
| `DOCKER` | `docker` | Docker executable |
| `CPMDISK` | `cpmdisk` | Host-side `cpmdisk` command |

## Build outputs

After a successful build, `bin/` contains:

| File | Description |
|------|-------------|
| `libplatform.lib` | Partner platform implementation required by `libcpm3-z80` |
| `libsdk.lib` | All Partner SDK functionality except platform hooks |
| `libcpm3-z80.lib` | Rebuilt CP/M 3 standard library |
| `libsdcc-z80.lib` | Rebuilt SDCC support library |
| `crt0cpm3-z80.rel` | CP/M 3 startup object; link this first |
| `include/partner/*.h` | Exported public SDK headers |
| `samples/*.com` | Built sample programs |
| `samples.img` | CP/M disk image containing the sample programs |

## Compiling your own program

Compile:

```sh
sdcc -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib \
  -Ibin/include -c -o myprog.rel myprog.c
```

Link:

```sh
sdcc -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib \
  --code-loc 0x100 --data-loc 0 \
  -o myprog.ihx \
  bin/crt0cpm3-z80.rel myprog.rel \
  bin/libplatform.lib bin/libsdk.lib \
  bin/libcpm3-z80.lib bin/libsdcc-z80.lib
```

Convert to `.COM`:

```sh
sdobjcopy -I ihex -O binary myprog.ihx myprog.com
```

Important notes:

- `crt0cpm3-z80.rel` must appear first on the link line
- your object files should come next
- `libplatform.lib` and `libsdk.lib` must be linked before `libcpm3-z80.lib`
- `libsdcc-z80.lib` must be linked last
- CP/M `.COM` programs must use `--code-loc 0x100 --data-loc 0`

## Samples

The `samples/` directory currently contains:

| Sample | Description |
|--------|-------------|
| `hello.c` | Minimal hello-world style example |
| `console.c` | Console I/O and debug API example |
| `mouse.c` | Serial mouse initialization and polling example |
| `terminal.c` | Serial communication example |

Build all samples and package them into a disk image:

```sh
make samples
```

## Public headers

The installed SDK exports these headers:

- `partner/bcd.h`
- `partner/clock.h`
- `partner/conio.h`
- `partner/debug.h`
- `partner/mouse.h`
- `partner/serial.h`
- `partner/timer.h`

## API reference

This section documents every public function exported by the SDK.

## partner/bcd.h

Packed BCD conversion helpers used by the clock code and available to user programs.

### `uint8_t bin2bcd(uint8_t bin)`

Converts an 8-bit binary value to packed BCD. For example, decimal `45` becomes `0x45`.

- Input is expected to be a decimal value that fits in two BCD digits
- Output stores the tens digit in the high nibble and the ones digit in the low nibble
- Useful when preparing `rtc_time_t` fields for manual low-level work

### `uint8_t bcd2bin(uint8_t bcd)`

Converts an 8-bit packed BCD value to plain binary.

- Input is expected to be a valid packed BCD value
- Output is the decoded decimal value
- Used internally by the RTC and timer helpers

## partner/clock.h

Clock, RTC, and BCD helpers. This header combines short-interval timing and wall-clock RTC access.

### Types

#### `rtc_time_t`

Binary representation of the Partner RTC state.

| Field | Meaning |
|-------|---------|
| `hsec` | Hundredths of a second |
| `sec` | Seconds |
| `min` | Minutes |
| `hour` | Hours |
| `wday` | Weekday |
| `mday` | Day of month |
| `month` | Month |
| `year` | Two-digit year |

### `uint8_t bin2bcd(uint8_t bin)`

Same BCD conversion helper as exported by `partner/bcd.h`.

### `uint8_t bcd2bin(uint8_t bcd)`

Same BCD conversion helper as exported by `partner/bcd.h`.

### `uint16_t timer_ms(void)`

Returns the current time within a rolling 60-second window, in milliseconds.

- Resolution is derived from the RTC subsecond registers
- The value wraps every 60 seconds
- Best suited for short-duration interval measurements, not absolute timestamps

### `int16_t timer(void)`

Returns the current time within a rolling 60-second window, in 1/100-second ticks.

- Lower resolution than `timer_ms()`
- Wraps every 60 seconds
- Useful for short polling loops and lightweight timeouts

### `int16_t timer_diff(uint16_t timer_start, uint16_t timer_offset)`

Computes a wrapped elapsed interval from a previous timer value.

- `timer_start` is the earlier timer reading
- `timer_offset` is a caller-supplied offset added before comparison
- Handles wraparound inside the 60-second timer window

### `void rtc_reset(void)`

Resets the RTC counters before reprogramming the clock.

- Used before writing a new RTC time
- Intended for clock control, not for generic timing loops

### `void rtc_reset_nvram(void)`

Resets the RTC NVRAM/flag area.

- This is part of the RTC support surface
- It does not reintroduce the old NVRAM storage API that was removed from the SDK

### `void rtc_get(rtc_time_t *t)`

Reads the current RTC date and time into `*t`.

- Output fields are returned in binary form, not packed BCD
- Caller must pass a valid pointer
- Intended for applications that need wall-clock time

### `void rtc_set(const rtc_time_t *t)`

Writes a new date and time to the RTC from `*t`.

- Input fields are expected in binary form
- Caller must pass a valid pointer
- Intended for setup/configuration utilities

## partner/conio.h

Console and text-screen helpers for the Partner display and keyboard path.

### Constants

Text attributes:

- `AT_NORMAL`
- `AT_BLINK`
- `AT_UNDERLINE`
- `AT_HIGHLIGHT`
- `AT_REVERSE`

Cursor modes:

- `NOCURSOR`
- `NORMALCURSOR`

### Types

#### `struct text_info`

Current text console state snapshot.

| Field | Meaning |
|-------|---------|
| `attr` | Current text attribute |
| `screenheight` | Screen height in rows |
| `screenwidth` | Screen width in columns |
| `curx` | Current cursor X position |
| `cury` | Current cursor Y position |

### `int kbhit(void)`

Checks whether a key is available without blocking.

- Returns `0` if no key is waiting
- Returns a non-zero value when input is ready
- Useful for non-blocking UI loops

### `void gotoxy(int x, int y)`

Moves the text cursor to the specified column and row.

- Coordinates are console coordinates, not raw video memory addresses
- Intended for absolute cursor positioning

### `void clrscr(void)`

Clears the text screen and resets the cursor to the home position.

- Fast full-screen clear path
- Useful before drawing menus or full-screen UIs

### `void setattr(unsigned char attr)`

Changes the current text attribute used by higher-level output routines.

- Accepts a combination of `AT_*` flags
- Affects later text output rather than rewriting existing screen cells

### `void gettextinfo(struct text_info *r)`

Stores the current text console state into `*r`.

- Caller must provide a valid pointer
- Useful for layout code that needs current dimensions or cursor position

### `int putch(int c)`

Writes a single character to the console using the current attribute.

- Intended for fast character output
- Returns the written character value

### `void rdchat(char *c, unsigned char *attr)`

Reads the character and attribute at the current cursor position.

- `c` receives the character
- `attr` receives the attribute byte
- Both pointers must be valid

### `int cputs(const char *str)`

Writes a zero-terminated string to the console.

- Uses the current attribute
- Does not require formatted I/O
- Returns the last written character value as an `int`

### `int wherex(void)`

Returns the current cursor X position.

### `int wherey(void)`

Returns the current cursor Y position.

### `void setcursortype(int cur_t)`

Changes cursor visibility.

- `NOCURSOR` hides the cursor
- `NORMALCURSOR` shows the cursor

### `void kbd_wait_ready(void)`

Waits until the keyboard/terminal path is ready for the next transfer.

- Low-level helper exposed publicly
- Useful only when writing very hardware-aware console code

### `void kbd_beep(bool long_beep)`

Triggers a short or long terminal beep.

- `false` produces a short beep
- `true` produces a longer beep sequence

### `char kbd_get_key(void)`

Reads one key from the keyboard path.

- Blocks until a key is available
- Returns a raw/normalized key value from the Partner keyboard handler

### `void scn2674_wait_mem_acc(void)`

Waits for a safe SCN2674 memory access window.

- Low-level display helper
- Mainly useful for direct screen-controller work

### `uint16_t scn2674_cursor_addr(void)`

Returns the current SCN2674 cursor address.

- Address is a controller/display-memory address, not a console `(x, y)` pair

### `void scn2674_cache_rows(void)`

Refreshes the internal cache of row base addresses.

- Used by higher-level text rendering helpers
- Normally not needed in simple applications

### `void scn2674_invalidate_row_cache(void)`

Invalidates the cached row base addresses.

- Forces a later refresh
- Useful if the screen start/pointer state changed outside the normal console helpers

### `uint16_t scn2674_rowptr(uint8_t row)`

Returns the display-memory base address for the specified row.

- `row` is a text row index
- Result is a raw controller memory address

### `void scn2674_cls(void)`

Clears the text screen using the SCN2674 fast path.

- Lower-level equivalent behind `clrscr()`

### `void scn2674_show_cursor(void)`

Enables the hardware text cursor.

### `void scn2674_hide_cursor(void)`

Disables the hardware text cursor.

### `void scn2674_xy(int x, int y)`

Moves the hardware cursor to console coordinates `(x, y)`.

- Lower-level equivalent behind `gotoxy()`

### `void scn2674_putchar(char ch, unsigned char attr)`

Writes a character and attribute directly through the SCN2674.

- `ch` is the character to write
- `attr` is the raw attribute byte

### `void scn2674_getchar(char *ch, unsigned char *attr)`

Reads a character and attribute through the SCN2674.

- `ch` receives the character
- `attr` receives the attribute
- Both pointers must be valid

## partner/debug.h

Low-level debug helpers for reading CPU state and arbitrary memory.

### Types

#### `z80_registers_t`

Snapshot of visible and shadow Z80 register state.

| Field | Meaning |
|-------|---------|
| `af`, `bc`, `de`, `hl` | Main register pairs |
| `ix`, `iy` | Index registers |
| `sp`, `pc` | Stack pointer and program counter |
| `af_shadow`, `bc_shadow`, `de_shadow`, `hl_shadow` | Shadow register pairs |
| `i`, `r` | Interrupt and refresh registers |

### `const z80_registers_t *z80_read_regs(void)`

Captures and returns a snapshot of the current register set.

- Returns a pointer to an internal/static snapshot buffer
- Useful for monitors, diagnostics, and debug UIs

### `uint8_t z80_read_mem(uint16_t address)`

Reads one byte from the specified memory address.

- Intended for debug/inspection use
- Does not allocate memory or change program state beyond the read

### `void z80_read_mem_block(uint8_t *dest, uint16_t source, uint16_t len)`

Copies a block of memory into `dest`.

- `source` is the starting memory address to inspect
- `len` is the number of bytes to copy
- Caller must provide a destination buffer large enough for `len` bytes

## partner/mouse.h

Streaming serial mouse support built on top of the SDK serial layer.

### Constants

Mouse protocol selectors:

- `MOUSE_MICROSOFT`
- `MOUSE_GENIUS_C7`
- `MOUSE_MOUSESYSTEMS`
- `MOUSE_LOGITECH` as a compatibility alias for `MOUSE_GENIUS_C7`

Button masks:

- `MOUSE_BUTTON_LEFT`
- `MOUSE_BUTTON_MIDDLE`
- `MOUSE_BUTTON_RIGHT`

### Types

#### `mouse_t`

Current decoded mouse state and decoder context.

| Field | Meaning |
|-------|---------|
| `type` | Active mouse protocol |
| `serial` | Underlying serial port object |
| `x`, `y` | Accumulated position |
| `dx`, `dy` | Latest decoded movement delta |
| `buttons` | Current button mask |
| `packet[5]` | Decoder scratch buffer |
| `count` | Current packet byte count |
| `synced` | Decoder synchronization state |

### `mouse_t *mouse_init(mouse_type_t type)`

Initializes a serial mouse decoder for the specified protocol.

- Allocates and returns a `mouse_t`
- Also initializes the serial port used for the mouse stream
- Returns `NULL` on allocation or initialization failure

### `void mouse_reset(mouse_t *mouse)`

Resets decoder synchronization and accumulated movement state.

- Does not free the object
- Useful after protocol desynchronization or manual re-centering

### `void mouse_poll(mouse_t *mouse)`

Polls the underlying serial port and decodes any pending mouse packet data.

- Non-blocking polling style
- Updates `dx`, `dy`, `buttons`, and accumulated position fields

### `void mouse_done(mouse_t *mouse)`

Releases all resources owned by the mouse object.

- Shuts down the associated serial object
- Frees the mouse state allocation

## partner/serial.h

Polling serial communication layer with configurable baud, framing, flow control, and buffered I/O.

### Types

#### `sio_flow_control`

Transmit/receive flow control mode.

- `SIO_FLOW_CONTROL_RTSCTS`
- `SIO_FLOW_CONTROL_XONXOFF`
- `SIO_FLOW_CONTROL_NONE`

#### `sio_bauds`

Baud-rate selector values understood by the SDK serial initializer.

- `SIO_BAUDS_153600`
- `SIO_BAUDS_9600`
- `SIO_BAUDS_4800`
- `SIO_BAUDS_2400`

#### `sio_stop_bits`

Stop-bit settings.

- `SIO_STOP_BITS_1`
- `SIO_STOP_BITS_2`

#### `sio_parity`

Parity settings.

- `SIO_PARITY_ODD`
- `SIO_PARITY_EVEN`
- `SIO_PARITY_NONE`

#### `sio_data_bits`

Word-length settings.

- `SIO_DATA_BITS_5`
- `SIO_DATA_BITS_6`
- `SIO_DATA_BITS_7`
- `SIO_DATA_BITS_8`

#### `sio_mode`

Serial operating mode.

- `SIO_MODE_POLLING`

#### `sio_exit_code`

Result code returned by `serial_exchange()`.

- `SIO_EXIT_CODE_NO_ACTIVITY`
- `SIO_EXIT_CODE_BUFFER_FULL`
- `SIO_EXIT_CODE_BUFFER_OVERFLOW`

#### `sio_port_addr`

Logical serial-port selector.

- `SIO_PORT_CRT`
- `SIO_PORT_LPT`
- `SIO_PORT_VAX`
- `SIO_PORT_MOD`

These are logical SDK port IDs, not raw hardware port numbers.

#### `sio_buffer`

Circular buffer state used for transmit and receive queues.

| Field | Meaning |
|-------|---------|
| `values` | Backing storage |
| `put_ptr` | Write index |
| `get_ptr` | Read index |
| `count` | Number of bytes currently stored |
| `size` | Total buffer capacity |

#### `sio_port`

Full serial-port state used by the SDK.

| Field | Meaning |
|-------|---------|
| `buffer_in` | Receive queue |
| `buffer_out` | Transmit queue |
| `no_activity_thr` | Poll-loop inactivity threshold |
| `in_buffer_ext` | Guard space before the input buffer is considered full |
| `wr5` | Cached transmit control register value |
| `addr` | Logical SDK port selector |
| `flow_control` | Active flow control mode |
| `xon_send` | XON/XOFF transmit state |
| `xon_rcv` | XON/XOFF receive state |

### `sio_port *serial_init(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds, sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity, sio_flow_control flow_control)`

Initializes a serial port with the SDK default buffer sizes.

- Returns a newly allocated `sio_port`
- Configures framing, baud, and flow control
- Returns `NULL` on failure

### `sio_port *serial_init_ex(sio_port_addr port_addr, sio_mode mode, sio_bauds bauds, sio_data_bits data_bits, sio_stop_bits stop_bits, sio_parity parity, sio_flow_control flow_control, uint16_t out_buffer_sz, uint16_t in_buffer_sz, uint16_t in_buffer_ext, uint16_t no_activity_thr)`

Initializes a serial port with explicit buffer sizes and polling thresholds.

- Use this when the default buffer sizing is not appropriate
- `in_buffer_ext` reserves headroom before the buffer is treated as effectively full
- `no_activity_thr` controls how long polling loops wait before reporting inactivity

### `bool serial_buffer_put(sio_buffer *buffer, uint16_t len, const uint8_t *values)`

Appends `len` bytes from `values` into a circular buffer.

- Returns `true` on success
- Returns `false` if the buffer does not have enough free space

### `bool serial_buffer_put_ch(sio_buffer *buffer, uint8_t ch)`

Appends a single byte to a circular buffer.

- Convenience wrapper over the generic buffer append path

### `bool serial_buffer_put_str(sio_buffer *buffer, const uint8_t *str)`

Appends a zero-terminated byte string to a circular buffer.

- Stops at the first zero byte
- Intended for queuing text output

### `bool serial_buffer_empty(sio_buffer *buffer)`

Returns whether a circular buffer currently contains no bytes.

### `uint8_t serial_buffer_get_ch(sio_buffer *buffer)`

Removes and returns one byte from a circular buffer.

- Caller is expected to ensure the buffer is not empty first

### `uint8_t serial_buffer_peek(sio_buffer *buffer, uint16_t idx)`

Reads a byte from the circular buffer without consuming it.

- `idx` is an offset relative to the current read position

### `uint16_t serial_buffer_get(sio_buffer *buffer, uint8_t *dest)`

Drains buffered data into `dest` and returns the number of copied bytes.

- Caller must provide enough space in `dest`
- Useful for retrieving a whole receive chunk at once

### `sio_exit_code serial_exchange(sio_port *port)`

Runs one polling send/receive exchange cycle.

- Processes pending transmit bytes
- Pulls any received bytes into the input buffer
- Returns an activity/overflow result code

### `bool serial_send(sio_port *port)`

Flushes queued transmit data as far as possible.

- Returns `true` when the transmit buffer is empty after the call
- Returns `false` if data remains queued

### `void serial_set_rts(sio_port *port, bool state)`

Asserts or deasserts RTS for the selected logical serial port.

- `true` enables RTS
- `false` clears RTS

### `bool serial_check_cts(sio_port *port)`

Reads the current CTS input state for the selected serial port.

- Returns `true` if CTS is asserted
- Used directly or as part of RTS/CTS flow-control handling

### `void serial_done(sio_port *port)`

Releases all resources associated with a serial port object.

- Frees input and output buffers
- Frees the `sio_port` allocation itself

## partner/timer.h

Top-level short-interval timer helpers.

These are a subset of the timing functions also exposed through `partner/clock.h`.

### `uint16_t timer_ms(void)`

Returns the current timer value in milliseconds inside a rolling 60-second window.

### `int16_t timer(void)`

Returns the current timer value in 1/100-second ticks inside a rolling 60-second window.

### `int16_t timer_diff(uint16_t timer_start, uint16_t timer_offset)`

Computes a wrapped elapsed interval from a previous timer reading and an offset.
