IMAGE ?= wischner/sdcc-z80-idp
DOCKER ?= docker
CPMDISK ?= cpmdisk

.PHONY: all build samples clean distclean shell

all: build

build:
	@mkdir -p build bin
	$(DOCKER) run --rm \
		-u $$(id -u):$$(id -g) \
		-v $(CURDIR):/work \
		-w /work/src \
		$(IMAGE) \
		make

samples: build
	@mkdir -p build bin
	$(DOCKER) run --rm \
		-u $$(id -u):$$(id -g) \
		-v $(CURDIR):/work \
		-w /work/samples \
		$(IMAGE) \
		make CPMDISK=$(CPMDISK) image

clean:
	$(DOCKER) run --rm \
		-u $$(id -u):$$(id -g) \
		-v $(CURDIR):/work \
		-w /work/src \
		$(IMAGE) \
		make clean
	rm -rf bin/samples.img

distclean: clean
	rm -rf build bin

shell:
	$(DOCKER) run --rm -it \
		-u $$(id -u):$$(id -g) \
		-v $(CURDIR):/work \
		-w /work \
		$(IMAGE) \
		/bin/sh
