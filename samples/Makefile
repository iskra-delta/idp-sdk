ROOT := ..
BUILD_DIR := $(ROOT)/build
BIN_DIR := $(ROOT)/bin
SAMPLES_BUILD_DIR := $(BUILD_DIR)/samples
SAMPLES_BIN_DIR := $(BIN_DIR)/samples
IMAGE_PATH := $(BIN_DIR)/samples.img
CPMDISK ?= cpmdisk

CC := sdcc
OBJCOPY := sdobjcopy
CFLAGS := -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib \
	-I$(ROOT)/include -I$(BIN_DIR)/include -I$(ROOT)/third_party/libcpm3-z80/include
LDFLAGS := -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib \
	--code-loc 0x100 --data-loc 0

CRT0 := $(BIN_DIR)/crt0cpm3-z80.rel
LOCAL_LIBRARIES := $(BIN_DIR)/libsdk.lib
CPM_LIB := $(BIN_DIR)/libcpm3-z80.lib
SDCC_LIB := $(BIN_DIR)/libsdcc-z80.lib
ALL_LIBRARIES := $(LOCAL_LIBRARIES) $(CPM_LIB) $(SDCC_LIB)

C_SOURCES := $(wildcard *.c)
REL_TARGETS := $(patsubst %.c,$(SAMPLES_BUILD_DIR)/%.rel,$(C_SOURCES))
IHX_TARGETS := $(patsubst %.c,$(SAMPLES_BUILD_DIR)/%.ihx,$(C_SOURCES))
COM_TARGETS := $(patsubst %.c,$(SAMPLES_BIN_DIR)/%.com,$(C_SOURCES))

.PHONY: all dirs image clean

all: dirs $(COM_TARGETS)

dirs:
	mkdir -p $(SAMPLES_BUILD_DIR) $(SAMPLES_BIN_DIR)

$(SAMPLES_BUILD_DIR)/%.rel: %.c $(CRT0) $(ALL_LIBRARIES) | dirs
	$(CC) $(CFLAGS) -c -o $@ $<

$(SAMPLES_BUILD_DIR)/%.ihx: $(SAMPLES_BUILD_DIR)/%.rel $(CRT0) $(ALL_LIBRARIES) | dirs
	$(CC) $(LDFLAGS) -o $@ $(CRT0) $< $(LOCAL_LIBRARIES) $(CPM_LIB) $(SDCC_LIB)

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
