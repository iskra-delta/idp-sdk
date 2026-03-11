IMAGE ?= wischner/sdcc-z80
DOCKER ?= docker
CPMDISK ?= cpmdisk

ROOT := $(CURDIR)
BUILD_DIR := $(ROOT)/build
BIN_DIR := $(ROOT)/bin
LIBSDCC_BUILD_DIR := $(BUILD_DIR)/libsdcc-z80
LIBCPM_BUILD_DIR := $(BUILD_DIR)/libcpm3-z80
SDK_BUILD_DIR := $(BUILD_DIR)/sdk
LIBSDCC_STAGE_DIR := $(BUILD_DIR)/stage/libsdcc-z80
LIBCPM_STAGE_DIR := $(BUILD_DIR)/stage/libcpm3-z80
LIBSDCC_ROOT := $(ROOT)/third_party/libsdcc-z80
LIBCPM_ROOT := $(ROOT)/third_party/libcpm3-z80
CPMDISK_ROOT := $(ROOT)/third_party/cpmdisk
CLI11_ROOT := $(ROOT)/third_party/CLI11
CPMDISK_BIN := $(CPMDISK_ROOT)/bin/cpmdisk
THIRD_PARTY_DIR := $(ROOT)/third_party

LIBSDCC_URL := https://github.com/retro-vault/libsdcc-z80
LIBCPM_URL := https://github.com/retro-vault/libcpm3-z80
CPMDISK_URL := https://github.com/iskra-delta/cpmdisk
CLI11_URL := https://github.com/CLIUtils/CLI11
CLI11_REF := v2.4.2

.PHONY: all build samples clean shell _build _sample-binaries _sample-image export-headers cpmdisk bootstrap-third-party

all: build samples

build: bootstrap-third-party
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)
	$(DOCKER) run --rm \
		-u $$(id -u):$$(id -g) \
		-v $(ROOT):/work \
		-w /work \
		$(IMAGE) \
		make _build

_build:
	$(MAKE) -C $(LIBSDCC_ROOT) \
		DOCKER=off \
		BUILD_DIR=$(LIBSDCC_BUILD_DIR) \
		BIN_DIR=$(LIBSDCC_STAGE_DIR)
	$(MAKE) -C $(LIBCPM_ROOT) \
		DOCKER=off \
		PLATFORM=PARTNER \
		BUILD_DIR=$(LIBCPM_BUILD_DIR) \
		BIN_DIR=$(LIBCPM_STAGE_DIR)
	mkdir -p $(BIN_DIR)
	cp $(LIBSDCC_STAGE_DIR)/libsdcc-z80.lib $(BIN_DIR)/
	cp $(LIBCPM_STAGE_DIR)/libcpm3-z80.lib $(BIN_DIR)/
	cp $(LIBCPM_STAGE_DIR)/crt0cpm3-z80.rel $(BIN_DIR)/
	rm -rf $(BIN_DIR)/include
	cp -R $(LIBCPM_STAGE_DIR)/include $(BIN_DIR)/
	$(MAKE) -C $(ROOT)/lib \
		BUILD_DIR=$(SDK_BUILD_DIR) \
		BIN_DIR=$(BIN_DIR) \
		INCLUDE_DIR=$(ROOT)/include \
		STDLIB_INCLUDE_DIR=$(LIBCPM_ROOT)/include
	$(MAKE) export-headers

export-headers:
	mkdir -p $(BIN_DIR)/include/partner
	rm -rf $(BIN_DIR)/include/partner
	rm -f $(BIN_DIR)/include/partner.h
	mkdir -p $(BIN_DIR)/include/partner
	cp $(ROOT)/include/partner/clock.h $(BIN_DIR)/include/partner/
	cp $(ROOT)/include/partner/conio.h $(BIN_DIR)/include/partner/
	cp $(ROOT)/include/partner/debug.h $(BIN_DIR)/include/partner/
	cp $(ROOT)/include/partner/mouse.h $(BIN_DIR)/include/partner/
	cp $(ROOT)/include/partner/serial.h $(BIN_DIR)/include/partner/

samples: build cpmdisk
	$(DOCKER) run --rm \
		-u $$(id -u):$$(id -g) \
		-v $(ROOT):/work \
		-w /work \
		$(IMAGE) \
		make _sample-binaries
	$(MAKE) _sample-image CPMDISK=$(CPMDISK_BIN)

_sample-binaries:
	$(MAKE) -C $(ROOT)/samples all

_sample-image:
	$(MAKE) -C $(ROOT)/samples image CPMDISK=$(CPMDISK)

cpmdisk: bootstrap-third-party
	cmake -S $(CPMDISK_ROOT) -B $(CPMDISK_ROOT)/build \
		-DCMAKE_BUILD_TYPE=Release \
		-DFETCHCONTENT_SOURCE_DIR_CLI11=$(CLI11_ROOT)
	cmake --build $(CPMDISK_ROOT)/build -j4

bootstrap-third-party:
	mkdir -p $(THIRD_PARTY_DIR)
	if [ ! -d $(LIBSDCC_ROOT) ]; then git clone --depth 1 $(LIBSDCC_URL) $(LIBSDCC_ROOT); fi
	if [ ! -d $(LIBCPM_ROOT) ]; then git clone --depth 1 $(LIBCPM_URL) $(LIBCPM_ROOT); fi
	if [ ! -d $(CPMDISK_ROOT) ]; then git clone --depth 1 $(CPMDISK_URL) $(CPMDISK_ROOT); fi
	if [ ! -d $(CLI11_ROOT) ]; then git clone --depth 1 --branch $(CLI11_REF) $(CLI11_URL) $(CLI11_ROOT); fi

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

shell:
	$(DOCKER) run --rm -it \
		-u $$(id -u):$$(id -g) \
		-v $(ROOT):/work \
		-w /work \
		$(IMAGE) \
		/bin/sh
