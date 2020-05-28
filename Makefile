DEBUG=0
PERF_TEST=0
HAVE_SHARED_CONTEXT=0

GIT_VERSION ?= " $(shell git rev-parse --short HEAD || echo unknown)"
ifneq ($(GIT_VERSION)," unknown")
	COREFLAGS += -DGIT_VERSION=\"$(GIT_VERSION)\"
endif

NAME   := parallel_n64_libretro
TARGETS := $(NAME).so
SHARED := -shared -Wl,--version-script=libretro/link.T
LDLIBS := -lpthread -lm
# FIXME: -lopengl32 is required for build, but shouldn't getprocaddress handle this?

DYNAFLAGS :=
COREFLAGS :=
CFLAGS  := -g3 -Wall -fPIC -flto

ifeq ($(DEBUG),1)
	CFLAGS += -Og
else
	CFLAGS += -O2 -ffast-math
	TARGETS += $(NAME).sym
endif

# Dirs
ROOT_DIR := .
LIBRETRO_DIR := $(ROOT_DIR)/libretro

# Cross compile ?
ifeq (,$(ARCH))
   ARCH = $(shell uname -m)
endif

# Dynarec requires libco to be enabled
#WITH_LIBCO ?= 1 # FIXME: Currently segfaults when libco disabled.
WITH_LIBCO := 1
ifeq ($(WITH_LIBCO),0)
	CFLAGS += -DNO_LIBCO
	WITH_DYNAREC := 0
endif

# If running on a reasonably fast architecture, use GLIDE64, which is slower
# but more accurate than GLN64
ifeq ($(ARCH), $(filter $(ARCH), i386 i686 x86_64 x64 aarch64))
	GFX_FAST ?= 0
else
	GFX_FAST ?= 1
endif

ifeq ($(GFX_FAST), 0)
	HAVE_GLN64=0
	HAVE_GLIDE64=1
else
	HAVE_GLN64=1
	HAVE_GLIDE64=0
endif

# Target Dynarec
WITH_DYNAREC ?= $(ARCH)
ifneq ($(WITH_DYNAREC),0)
	DYNAFLAGS += -DDYNAREC
ifeq ($(ARCH), $(filter $(ARCH), i386 i686))
	WITH_DYNAREC = x86
else ifeq ($(ARCH), $(filter $(ARCH), x86_64 x64))
	WITH_DYNAREC = x86_64
else ifeq ($(ARCH), $(filter $(ARCH), arm))
	WITH_DYNAREC = arm
else ifeq ($(ARCH), $(filter $(ARCH), aarch64))
	WITH_DYNAREC = aarch64
endif
endif

include Makefile.common

ifeq ($(HAVE_NEON), 1)
   COREFLAGS += -DHAVE_NEON
endif

ifeq ($(PERF_TEST), 1)
   COREFLAGS += -DPERF_TEST
endif

ifeq ($(HAVE_SHARED_CONTEXT), 1)
   COREFLAGS += -DHAVE_SHARED_CONTEXT
endif

COREFLAGS += -D__LIBRETRO__ -DM64P_PLUGIN_API -DM64P_CORE_PROTOTYPES -D_ENDUSER_RELEASE -DSINC_LOWER_QUALITY

ifneq (,$(findstring msvc,$(platform)))
CFLAGS += -DINLINE="_inline"
else
CFLAGS += -DINLINE="inline"
endif

### Finalize ###
OBJECTS     += $(SOURCES_CXX:.cpp=.o) $(SOURCES_C:.c=.o) $(SOURCES_ASM:.S=.o)
CFLAGS      += $(COREFLAGS) $(CPUFLAGS) $(DYNAFLAGS)
CXXFLAGS    += $(CFLAGS)

all: $(TARGETS)
$(NAME).so: $(OBJECTS)
	$(CC) $(SHARED) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(NAME).sym: $(NAME).so
	strip --only-keep-debug -o $@ $<
	strip -s $<
	@chmod -x $@

%.o: %.S
	nasm -f elf64 $< -o$@

clean:
	$(RM) $(OBJECTS) $(TARGETS)

# 80char      |-------------------------------------------------------------------------------|
help:
	@echo "Available options and their descriptions when enabled:"
	@echo "  DEBUG=$(DEBUG)"
	@echo "          Enables all asserts and reduces optimisation."
	@echo "  GFX_FAST=$(GFX_FAST)"
	@echo "          Selects either a fast or accuracte graphics plugin."
	@echo "          If not set, a setting will be automatically selected based upon the"
	@echo "          target architecture."
	@echo
	@echo "Advanced options:"
	@echo "  WITH_DYNAREC=$(WITH_DYNAREC)"
	@echo "  WITH_LIBCO=$(WITH_LIBCO)"
	@echo

.PHONY: clean
