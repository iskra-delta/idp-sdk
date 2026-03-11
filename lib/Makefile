ROOT ?= ..
BUILD_DIR ?= $(ROOT)/build/local
BIN_DIR ?= $(ROOT)/bin
INCLUDE_DIR ?= $(ROOT)/include
INTERNAL_INCLUDE_DIR ?= $(ROOT)/lib/include
STDLIB_INCLUDE_DIR ?= $(ROOT)/third_party/libcpm3-z80/include

LIBPLATFORM := $(BIN_DIR)/libplatform.lib
LIBSDK := $(BIN_DIR)/libsdk.lib

CC := sdcc
AS := sdasz80
AR := sdar
CFLAGS := -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib --debug \
	-I$(INCLUDE_DIR) -I$(INTERNAL_INCLUDE_DIR) -I$(STDLIB_INCLUDE_DIR) \
	-DPLATFORM_PARTNER -DPLATFORM_NAME=PARTNER
ASFLAGS := -xlos -g

PARTNER_C_SOURCES := \
	./src/partner/platform.c

CONIO_C_SOURCES := \
	./src/conio/cputs.c \
	./src/conio/clrscr.c \
	./src/conio/gettextinfo.c \
	./src/conio/gotoxy.c \
	./src/conio/kbhit.c \
	./src/conio/putch.c \
	./src/conio/rdchat.c \
	./src/conio/setattr.c \
	./src/conio/setcursortype.c \
	./src/conio/_setup_width.c \
	./src/conio/_state.c \
	./src/conio/wherex.c \
	./src/conio/wherey.c
CONIO_ASM_SOURCES := \
	./src/conio/scn2674_cache_data.s \
	./src/conio/scn2674_cache_rows.s \
	./src/conio/scn2674_cls.s \
	./src/conio/scn2674_cursor_addr.s \
	./src/conio/scn2674_getchar.s \
	./src/conio/scn2674_hide_cursor.s \
	./src/conio/scn2674_invalidate_row_cache.s \
	./src/conio/scn2674_putchar.s \
	./src/conio/scn2674_rowptr.s \
	./src/conio/scn2674_rowptr_raw.s \
	./src/conio/scn2674_show_cursor.s \
	./src/conio/scn2674_wait_mem_acc.s \
	./src/conio/scn2674_xy.s \
	./src/conio/kbd_beep.s \
	./src/conio/kbd_get_key.s \
	./src/conio/kbd_wait_ready.s \
	./src/conio/scn2674_cursor_off.s \
	./src/conio/scn2674_cursor_on.s \
	./src/conio/scn2674_get_cursor.s \
	./src/conio/scn2674_set_cursor.s \
	./src/conio/scn2674_set_pointer.s \
	./src/conio/scn2674_wait_rdy.s

SERIAL_C_SOURCES := \
	./src/serial/_buffer_alloc_internal.c \
	./src/serial/buffer_empty.c \
	./src/serial/buffer_get.c \
	./src/serial/buffer_get_ch.c \
	./src/serial/buffer_peek.c \
	./src/serial/buffer_put.c \
	./src/serial/buffer_put_ch.c \
	./src/serial/buffer_put_str.c \
	./src/serial/_check_able_to_send.c \
	./src/serial/_check_ch_available.c \
	./src/serial/check_cts.c \
	./src/serial/_check_tx_buffer_empty.c \
	./src/serial/serial_done.c \
	./src/serial/exchange.c \
	./src/serial/_flush.c \
	./src/serial/serial_init.c \
	./src/serial/init_ex.c \
	./src/serial/_init_params.c \
	./src/serial/send.c \
	./src/serial/_send_ch_force.c \
	./src/serial/_set_able_to_rcv.c \
	./src/serial/set_rts.c
SERIAL_ASM_SOURCES := \
	./src/serial/_serial_port_in.s \
	./src/serial/_serial_port_out.s

MOUSE_C_SOURCES := \
	./src/mouse/_apply_packet.c \
	./src/mouse/mouse_done.c \
	./src/mouse/_feed_microsoft.c \
	./src/mouse/_feed_mousesystems.c \
	./src/mouse/mouse_init.c \
	./src/mouse/poll.c \
	./src/mouse/mouse_reset.c \
	./src/mouse/_reset_decoder.c

CLOCK_C_SOURCES := \
	./src/clock/cs10.c \
	./src/clock/timer.c \
	./src/clock/timer_diff.c \
	./src/clock/timer_ms.c
CLOCK_ASM_SOURCES := \
	./src/clock/rtc_get.s \
	./src/clock/rtc_reset.s \
	./src/clock/rtc_reset_nvram.s \
	./src/clock/rtc_set.s \
	./src/clock/bcd2bin.s \
	./src/clock/bin2bcd.s

DEBUG_C_SOURCES :=
DEBUG_ASM_SOURCES := \
	./src/debug/z80_read_mem.s \
	./src/debug/z80_read_mem_block.s \
	./src/debug/z80_read_regs.s \
	./src/debug/z80_state.s

PARTNER_OBJECTS := \
	$(patsubst ./%.c,$(BUILD_DIR)/%.rel,$(PARTNER_C_SOURCES))
SDK_OBJECTS := \
	$(patsubst ./%.c,$(BUILD_DIR)/%.rel,$(CONIO_C_SOURCES)) \
	$(patsubst ./%.s,$(BUILD_DIR)/%.rel,$(CONIO_ASM_SOURCES)) \
	$(patsubst ./%.c,$(BUILD_DIR)/%.rel,$(SERIAL_C_SOURCES)) \
	$(patsubst ./%.s,$(BUILD_DIR)/%.rel,$(SERIAL_ASM_SOURCES)) \
	$(patsubst ./%.c,$(BUILD_DIR)/%.rel,$(MOUSE_C_SOURCES)) \
	$(patsubst ./%.c,$(BUILD_DIR)/%.rel,$(CLOCK_C_SOURCES)) \
	$(patsubst ./%.s,$(BUILD_DIR)/%.rel,$(CLOCK_ASM_SOURCES)) \
	$(patsubst ./%.c,$(BUILD_DIR)/%.rel,$(DEBUG_C_SOURCES)) \
	$(patsubst ./%.s,$(BUILD_DIR)/%.rel,$(DEBUG_ASM_SOURCES))

.PHONY: all clean dirs

all: dirs $(LIBPLATFORM) $(LIBSDK)

dirs:
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR)/%.rel: %.c | dirs
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.rel: %.s | dirs
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

$(LIBPLATFORM): $(PARTNER_OBJECTS) | dirs
	rm -f $@
	$(AR) rcs $@ $(PARTNER_OBJECTS)

$(LIBSDK): $(SDK_OBJECTS) | dirs
	rm -f $@
	$(AR) rcs $@ $(SDK_OBJECTS)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(LIBPLATFORM) $(LIBSDK)
