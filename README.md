Mupen64plus-libretro-nx is significantly faster than Parallel-N64.

* Mupen64plus-libretro-nx: 1344.65 FPS
* Parallel-N64: 754.22 FPS

This project will be archived.

# Toplel-N64

This is a fork of parallel-N64. The aim is to produce a small, OpenGL-only,
libretro core.  Features such as MSVC builds, Vulkan, and advanced
configuration are completely removed.

The produced binary is licensed under GPLv3. Each source file may be licensed
differently however.

Only tested on Linux x86_64.

Some options may be set at compile time to configure toplel-N64. Execute `make
help` to see all the available options.

### Graphic plugins

Toplel-N64 comes with only two graphics plugin: GLN64 and Glide64. The former
is considered the "fast" plugin, whilst the latter is slower but has higher
accuracy. The graphics plugin may be manually selected at compile time by
using:

* `make GFX_FAST=1`
* `make GFX_FAST=0`

Note that both plugins require OpenGL. There is no software rendering or Vulkan
support. Please see Parallel-N64 if you prefer these options.

### Dynarec

Dynamic recompilation (dynarec) can be used to increase emulation performance.
Compatibility with dynarec is checked when building, but may be manually set to
the values below:

* make WITH_DYNAREC=x86
* make WITH_DYNAREC=x86_64
* make WITH_DYNAREC=arm
* make WITH_DYNAREC=aarch64

### Benchmarks

As of commit b86922d904fcc79615fce879a36cd4b436d94990:

* `make GFX_FAST=0 CPUFLAGS="-mtune=haswell"`, Glide64: 622.37 FPS
* `make GFX_FAST=1 CPUFLAGS="-mtune=haswell"`, GLN64:   754.22 FPS
