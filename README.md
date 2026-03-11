# idp-sdk

Static SDK for the Iskra Delta Partner, built on top of `libcpm3-z80` and `libsdcc-z80`.

## Table of contents

- [Introduction](#introduction)
- [Building the SDK](#building-the-sdk)
- [Compiling your CP/M program](#compiling-your-cpm-program)
- [Samples](#samples)
- [Source Tree Layout](#source-tree-layout)
- [Public Headers](#public-headers)

## Introduction

**idp-sdk** packages everything needed to build CP/M 3 programs for the Iskra Delta Partner:

- `libsdk.lib` with Partner-specific platform hooks and SDK functionality
- `libcpm3-z80.lib` rebuilt for `partner`
- `libsdcc-z80.lib`
- `crt0cpm3-z80.rel`
- one merged `include/` tree under `bin/`

The SDK library contains:

- Partner platform initialization
- console I/O
- serial support
- mouse support
- clock helpers
- debug helpers

The build output is intentionally packaged the same way as `libcpm3-z80`: final artifacts go to `bin/`, intermediate files go to `build/`, and both `BUILD_DIR` and `BIN_DIR` are overridable.

This repository is fixed to the Iskra Delta Partner. The platform is always `partner` and is not a user-configurable build parameter.

## Building the SDK

Clone the repository first:

```sh
git clone https://github.com/iskra-delta/idp-sdk.git
cd idp-sdk
```

### Commands

| Command | Description |
|---------|-------------|
| `make` | Build everything: libraries, CRT0, headers, sample programs, and sample disk image |
| `make clean` | Remove `build/` and `bin/` |

### Parameters

| Parameter | Values | Default | Description |
|-----------|--------|---------|-------------|
| `DOCKER` | `on`, `off` | `on` | `on` builds inside the `wischner/sdcc-z80` Docker image. `off` builds natively and requires the toolchain on `PATH`. |
| `BUILD_DIR` | path | `build/` | Intermediate build products. |
| `BIN_DIR` | path | `bin/` | Final outputs: libraries, CRT0, headers, samples. |

Examples:

```sh
make                          # build everything in Docker
make DOCKER=off               # build everything natively
make DOCKER=off BUILD_DIR=out/build BIN_DIR=out/bin
```

### Output files

All outputs are placed in `bin/` (or `BIN_DIR` if overridden). A normal `make` produces:

| File | Description |
|------|-------------|
| `libsdk.lib` | Partner SDK archive, including platform hooks |
| `libcpm3-z80.lib` | CP/M 3 standard C library rebuilt for `partner` |
| `libsdcc-z80.lib` | SDCC runtime support library |
| `crt0cpm3-z80.rel` | C runtime start-up object; must be linked first |
| `include/` | Merged public headers from `libcpm3-z80` and `idp-sdk` |
| `samples/*.com` | Built sample programs |
| `samples.img` | CP/M disk image containing the sample programs |

### Notes

- `libsdk.lib` now includes the Partner platform implementation. There is no separate `libplatform.lib`.
- Third-party source trees are bootstrapped into `third_party/` on demand.
- `cpmdisk` is built locally on the host; the Z80 libraries are built either inside Docker or natively depending on `DOCKER`.

## Compiling your CP/M program

You need SDCC installed locally, or you can use the default Docker-based `make` flow.

Compile:

```sh
sdcc -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib \
     -I bin/include -c -o myprog.rel myprog.c
```

Link:

```sh
sdcc -mz80 --std-c11 --no-std-crt0 --nostdinc --nostdlib \
     --code-loc 0x100 --data-loc 0 \
     -o myprog.ihx \
     bin/crt0cpm3-z80.rel myprog.rel \
     bin/libsdk.lib bin/libcpm3-z80.lib bin/libsdcc-z80.lib
```

Convert to `.COM`:

```sh
sdobjcopy -I ihex -O binary myprog.ihx myprog.com
```

Important notes:

- `crt0cpm3-z80.rel` must appear first on the link line
- your object files come next
- `libsdk.lib` should be linked before `libcpm3-z80.lib`
- `libsdcc-z80.lib` should be linked last
- CP/M `.COM` programs must use `--code-loc 0x100 --data-loc 0`

## Samples

The `samples/` directory contains small working programs for the SDK:

| Sample | Description |
|--------|-------------|
| `hello.c` | Minimal hello-world example |
| `console.c` | Console output and screen API example |
| `mouse.c` | Serial mouse initialization and polling example |
| `terminal.c` | Serial terminal example |

They are built and packaged automatically by `make`:

```sh
make
```

## Source Tree Layout

| Path | Purpose |
|------|---------|
| `include/partner/` | Public SDK headers |
| `lib/src/` | SDK implementation |
| `lib/include/` | Internal SDK headers and hardware definitions |
| `samples/` | Example programs |
| `third_party/libcpm3-z80/` | Vendored CP/M 3 standard library |
| `third_party/libsdcc-z80/` | Vendored SDCC support library |
| `third_party/cpmdisk/` | Disk image tool used for sample packaging |
| `bin/` | Final packaged outputs |
| `build/` | Intermediate build artifacts |

## Public Headers

The packaged `bin/include/` tree contains:

- standard and CP/M headers from `libcpm3-z80`
- Partner SDK headers under `partner/`

The current public Partner headers are:

- `partner/bcd.h`
- `partner/clock.h`
- `partner/conio.h`
- `partner/debug.h`
- `partner/mouse.h`
- `partner/serial.h`
- `partner/timer.h`
