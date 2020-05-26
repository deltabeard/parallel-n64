# toplel-n64

This is a fork of parallel-n64. The aim is to produce a small, OpenGL, libretro core.
Features such as MSVC builds, Vulkan, and advanced configuration are completely removed.

The produced binary is licensed under GPLv3. Each source file may be licensed differently however.

Only tested on Linux x86_64.

Dynamic recompilation (dynarec) can be used to increase emulation performance.
Compatibility with dynarec is checked when building, but may be manually set to
the values below:

* make WITH_DYNAREC=x86
* make WITH_DYNAREC=x86_64
* make WITH_DYNAREC=arm
* make WITH_DYNAREC=aarch64

Additional make options:
* HAVE_NEON
