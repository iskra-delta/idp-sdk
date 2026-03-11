ROOT := ..
BUILD_DIR := $(ROOT)/build
BIN_DIR := $(ROOT)/bin
INCLUDE_DIR := $(ROOT)/include
EXPORT_INCLUDE_DIR := $(BIN_DIR)/include
LIB_NAME := libpartner.lib
LIB_PATH := $(BIN_DIR)/$(LIB_NAME)

CC := sdcc
AS := sdasz80
AR := sdar
CFLAGS := -I$(INCLUDE_DIR)
ASFLAGS := -o

C_SOURCES := $(shell find . -name '*.c' -print)
ASM_SOURCES := $(shell find . -name '*.s' -print)
REL_OBJECTS := \
	$(patsubst ./%.c,$(BUILD_DIR)/%.rel,$(C_SOURCES)) \
	$(patsubst ./%.s,$(BUILD_DIR)/%.rel,$(ASM_SOURCES))

.PHONY: all clean dirs export-headers

all: dirs $(LIB_PATH) export-headers

dirs:
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR)/%.rel: %.c | dirs
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.rel: %.s | dirs
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $@ $<

$(LIB_PATH): $(REL_OBJECTS) | dirs
	rm -f $@
ifneq ($(strip $(REL_OBJECTS)),)
	$(AR) rcs $@ $(REL_OBJECTS)
else
	@echo "No source files found in src/. Add .c or .s files, then rebuild."
endif

export-headers: | dirs
	rm -rf $(EXPORT_INCLUDE_DIR)
	mkdir -p $(EXPORT_INCLUDE_DIR)
	cp -R $(INCLUDE_DIR)/* $(EXPORT_INCLUDE_DIR)/

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
