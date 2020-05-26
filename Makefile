DEBUG=0
PERF_TEST=0
HAVE_SHARED_CONTEXT=0
WITH_CRC=brumme
HAVE_OPENGL=1
HAVE_RSP_DUMP=0
HAVE_RDP_DUMP=0
HAVE_PARALLEL_RSP=0
HAVE_LTCG ?= 0

GIT_VERSION ?= " $(shell git rev-parse --short HEAD || echo unknown)"
ifneq ($(GIT_VERSION)," unknown")
	COREFLAGS += -DGIT_VERSION=\"$(GIT_VERSION)\"
endif

TARGET := parallel-n64_libretro.so
SHARED := -shared -Wl,--version-script=libretro/link.T
LDFLAGS += -lpthread -lGL

DYNAFLAGS :=
INCFLAGS  :=
COREFLAGS :=
CPUFLAGS  := -O2
GLFLAGS   :=

fpic = -fpic

UNAME=$(shell uname -a)

# Dirs
ROOT_DIR := .
LIBRETRO_DIR := $(ROOT_DIR)/libretro

# Cross compile ?
ifeq (,$(ARCH))
   ARCH = $(shell uname -m)
endif

# Target Dynarec
WITH_DYNAREC = $(ARCH)

ifeq ($(ARCH), $(filter $(ARCH), i386 i686))
   WITH_DYNAREC = x86
else ifeq ($(ARCH), $(filter $(ARCH), arm))
   WITH_DYNAREC = arm
else ifeq ($(ARCH), $(filter $(ARCH), aarch64))
   WITH_DYNAREC = aarch64
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
CXXFLAGS += -DINLINE="_inline"
else
CFLAGS += -DINLINE="inline"
CXXFLAGS += -DINLINE="inline"
endif

# Fix for GCC 10, make sure its added to all stages of the compiler
ifeq "$(shell expr `gcc -dumpversion` \>= 10)" "1"
  CPUFLAGS += -fcommon
endif

# LTO
ifeq ($(HAVE_LTCG),1)
  CPUFLAGS += -flto
endif

ASFLAGS     := $(ASFLAGS) $(CFLAGS) $(CPUFLAGS)

### Finalize ###
OBJECTS     += $(SOURCES_CXX:.cpp=.o) $(SOURCES_C:.c=.o) $(SOURCES_ASM:.S=.o)
CXXFLAGS    += $(CPUOPTS) $(COREFLAGS) $(INCFLAGS) $(INCFLAGS_PLATFORM) $(fpic) $(PLATCFLAGS) $(CPUFLAGS) $(DYNAFLAGS) $(GLFLAGS)
CFLAGS      += $(CPUOPTS) $(COREFLAGS) $(INCFLAGS) $(INCFLAGS_PLATFORM) $(fpic) $(PLATCFLAGS) $(CPUFLAGS) $(DYNAFLAGS) $(GLFLAGS)

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(SHARED) $(CFLAGS) $(LDFLAGS) $(GL_LIB) $(LIBS) -o $@ $(OBJECTS) 

clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: clean
