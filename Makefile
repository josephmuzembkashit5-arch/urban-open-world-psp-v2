TARGET = urban_open_world
OBJS = src/main.o

INCDIR =
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBS = -lpspgum -lpspgu -lpspdisplay -lpspge -lpspctrl -lpspkernel -lm

BUILD_PRX = 1
PSP_FW_VERSION = 660

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Urban Open World PSP Prototype

include $(PSPSDK)/lib/build.mak
