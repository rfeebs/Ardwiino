#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

MCU          = atmega16u2
ARCH         = AVR8
BOARD        = UNO
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
SRC          = $(shell find ../../shared/controller/output -type f -name '*.c*') ../../shared/sharedmain.cpp ../../shared/config/eeprom.c ../../shared/io/uart/uart.c  ../../shared/io/bootloader/Bootloader.cpp ../../shared/io/lufa/Descriptors.c main.cpp $(LUFA_SRC_USBCLASS) $(LUFA_SRC_USB)
LUFA_PATH    = ../../shared/io/lufa/lufa/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -I../../shared/io/lufa
CPP_FLAGS	 = -std=c++11
LD_FLAGS     =
OBJDIR		 = obj
BIN		 	 = bin
TARGET       = $(BIN)/ardwiino-uno-usb
AVRDUDE_PROGRAMMER = avr109
AVRDUDE_FLAGS = -b 57600 -P /dev/ttyACM0 reset
$(info $(shell mkdir -p $(BIN)))

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
