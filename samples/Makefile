ROOT := ..
BUILD_DIR := $(ROOT)/build
BIN_DIR := $(ROOT)/bin
SAMPLES_BUILD_DIR := $(BUILD_DIR)/samples
SAMPLES_BIN_DIR := $(BIN_DIR)/samples
LIB_INCLUDE_DIR := $(BIN_DIR)/include
LIB_PATH := $(BIN_DIR)/libpartner.lib
IMAGE_PATH := $(BIN_DIR)/samples.img
CPMDISK ?= cpmdisk

export PATH := /opt/sdcc/bin:$(PATH)

CC := sdcc
OBJCOPY := sdobjcopy
CFLAGS := -I$(LIB_INCLUDE_DIR)

C_SOURCES := $(wildcard *.c)
IHX_TARGETS := $(patsubst %.c,$(SAMPLES_BUILD_DIR)/%.ihx,$(C_SOURCES))
COM_TARGETS := $(patsubst %.c,$(SAMPLES_BIN_DIR)/%.com,$(C_SOURCES))

.PHONY: all dirs image clean

all: dirs $(COM_TARGETS)

dirs:
	mkdir -p $(SAMPLES_BUILD_DIR) $(SAMPLES_BIN_DIR)

$(SAMPLES_BUILD_DIR)/%.ihx: %.c $(LIB_PATH) | dirs
	$(CC) $(CFLAGS) $< $(LIB_PATH) -o $@

$(SAMPLES_BIN_DIR)/%.com: $(SAMPLES_BUILD_DIR)/%.ihx | dirs
	$(OBJCOPY) -I ihex -O binary $< $@

image: all
	rm -f $(IMAGE_PATH)
	$(CPMDISK) create $(IMAGE_PATH) fdd
ifneq ($(strip $(COM_TARGETS)),)
	$(CPMDISK) add $(IMAGE_PATH) $(COM_TARGETS)
endif

clean:
	rm -rf $(SAMPLES_BUILD_DIR) $(SAMPLES_BIN_DIR) $(IMAGE_PATH)
