ifneq ($(shell uname), Linux)
$(error OS must be Linux!)
endif

export ROOT        = $(realpath .)
export BUILD_DIR  ?= $(ROOT)/build
export BIN_DIR    ?= $(ROOT)/bin

PLATFORM           = partner
DOCKER            ?= on

DOCKER_IMAGE      = wischner/sdcc-z80
DOCKER_RUN        = docker run --rm \
                    -v "$(ROOT)":/src \
                    -w /src \
                    -e INSIDE_DOCKER=1 \
                    -e PLATFORM=$(PLATFORM) \
                    --user $(shell id -u):$(shell id -g) \
                    $(DOCKER_IMAGE)

LIBSDCC_STAGE_DIR = $(BUILD_DIR)/stage/libsdcc-z80
LIBCPM_STAGE_DIR  = $(BUILD_DIR)/stage/libcpm3-z80
SDK_STAGE_DIR     = $(BUILD_DIR)/stage/sdk

LIBSDCC_ROOT      = $(ROOT)/third_party/libsdcc-z80
LIBCPM_ROOT       = $(ROOT)/third_party/libcpm3-z80
CPMDISK_ROOT      = $(ROOT)/third_party/cpmdisk
CLI11_ROOT        = $(ROOT)/third_party/CLI11
CPMDISK_BIN       = $(CPMDISK_ROOT)/bin/cpmdisk
THIRD_PARTY_DIR   = $(ROOT)/third_party

LIBSDCC_URL       = https://github.com/retro-vault/libsdcc-z80
LIBCPM_URL        = https://github.com/retro-vault/libcpm3-z80
CPMDISK_URL       = https://github.com/iskra-delta/cpmdisk
CLI11_URL         = https://github.com/CLIUtils/CLI11
CLI11_REF         = v2.4.2

ifndef INSIDE_DOCKER
ifeq ($(DOCKER),off)
REQUIRED = make git cmake sdcc sdar sdasz80 sdcpp sdldz80
K := $(foreach exec,$(REQUIRED),\
    $(if $(shell which $(exec)),,$(error "$(exec) not found. Install prerequisites or use DOCKER=on.")))
endif
endif

.PHONY: all _all _build _sample-binaries _sample-image clean cpmdisk bootstrap-third-party $(BUILD_DIR)

.DEFAULT_GOAL := all

ifeq ($(DOCKER),on)
all:
	$(DOCKER_RUN) make _build
	$(DOCKER_RUN) make _sample-binaries
	$(MAKE) cpmdisk
	$(MAKE) _sample-image CPMDISK=$(CPMDISK_BIN)
else
all: _all
endif

_all: _build cpmdisk _sample-binaries
	$(MAKE) _sample-image CPMDISK=$(CPMDISK_BIN)

_build: bootstrap-third-party $(BUILD_DIR)
	$(MAKE) -C $(LIBSDCC_ROOT) \
		DOCKER=off \
		BUILD_DIR=$(BUILD_DIR)/libsdcc-z80 \
		BIN_DIR=$(LIBSDCC_STAGE_DIR)
	$(MAKE) -C $(LIBCPM_ROOT) \
		DOCKER=off \
		PLATFORM=$(PLATFORM) \
		BUILD_DIR=$(BUILD_DIR)/libcpm3-z80 \
		BIN_DIR=$(LIBCPM_STAGE_DIR)
	$(MAKE) -C $(ROOT)/lib \
		BUILD_DIR=$(BUILD_DIR)/sdk \
		BIN_DIR=$(SDK_STAGE_DIR) \
		INCLUDE_DIR=$(ROOT)/include \
		STDLIB_INCLUDE_DIR=$(ROOT)/third_party/libcpm3-z80/include
	cp --dereference $(LIBSDCC_STAGE_DIR)/libsdcc-z80.lib $(BIN_DIR)
	cp --dereference $(LIBCPM_STAGE_DIR)/libcpm3-z80.lib $(BIN_DIR)
	cp --dereference $(LIBCPM_STAGE_DIR)/crt0cpm3-z80.rel $(BIN_DIR)/crt0cpm3-z80.rel
	cp --dereference $(SDK_STAGE_DIR)/libsdk.lib $(BIN_DIR)
	cp -R --dereference $(LIBCPM_STAGE_DIR)/include $(BIN_DIR)
	cp -R --dereference $(ROOT)/include/. $(BIN_DIR)/include/

$(BUILD_DIR):
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

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
