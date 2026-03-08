ROOT := ..
BIN_DIR := $(ROOT)/bin
SAMPLES_BIN_DIR := $(BIN_DIR)/samples
LIB_INCLUDE_DIR := $(BIN_DIR)/include
LIB_PATH := $(BIN_DIR)/libpartner.lib
CPM3_INCLUDE_DIR := /opt/libraries/libcpm3-z80/include
CPM3_CRT0 := /opt/libraries/libcpm3-z80/lib/crt0cpm3-z80.rel
CPM3_LIB := /opt/libraries/libcpm3-z80/lib/libcpm3-z80.lib
SDCC_LIB := /opt/libraries/libsdcc-z80/lib/libsdcc-z80.lib
IMAGE_PATH := $(BIN_DIR)/samples.img
CPMDISK ?= cpmdisk

export PATH := /opt/sdcc/bin:$(PATH)

CC := sdcc
MAKEBIN := makebin
CFLAGS := -mz80 --nostdlib --no-std-crt0 --code-loc 0x100 -I$(CPM3_INCLUDE_DIR) -I$(LIB_INCLUDE_DIR)

C_SOURCES := $(wildcard *.c)
IHX_TARGETS := $(patsubst %.c,$(SAMPLES_BIN_DIR)/%.ihx,$(C_SOURCES))
COM_TARGETS := $(patsubst %.c,$(SAMPLES_BIN_DIR)/%.com,$(C_SOURCES))

.PHONY: all dirs image clean

all: dirs $(COM_TARGETS)

dirs:
	mkdir -p $(SAMPLES_BIN_DIR)

$(SAMPLES_BIN_DIR)/%.ihx: %.c $(LIB_PATH) | dirs
	$(CC) $(CFLAGS) $< $(CPM3_CRT0) $(LIB_PATH) $(CPM3_LIB) $(SDCC_LIB) -o $@

$(SAMPLES_BIN_DIR)/%.com: $(SAMPLES_BIN_DIR)/%.ihx | dirs
	$(MAKEBIN) -p $< $@

image: all
	rm -f $(IMAGE_PATH)
	$(CPMDISK) create $(IMAGE_PATH) fdd
ifneq ($(strip $(COM_TARGETS)),)
	$(CPMDISK) add $(IMAGE_PATH) $(COM_TARGETS)
endif

clean:
	rm -rf $(SAMPLES_BIN_DIR) $(IMAGE_PATH)
