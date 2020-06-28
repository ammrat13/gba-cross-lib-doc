# Makefile for LibGCCMem
# By: Ammar Ratnani
#
# This file will simply compile the one file in this library, turn it into an 
# archive for linking, then move it to the right place.

# Sensitive to these environment variables
PREFIX ?= $(HOME)/gba-cross-lib-doc
TARGET ?= arm-agb-eabi

# Find where everything is and where to install
PROGRAM_DIR := $(PREFIX)/toolchain/bin
INSTALL_LIB_DIR := $(PREFIX)/lib
INSTALL_INC_DIR := $(PREFIX)/include

# Get the locations for all the programs
PROGRAM_PREFIX := $(PROGRAM_DIR)/$(TARGET)-
CC := $(PROGRAM_PREFIX)gcc
AR := $(PROGRAM_PREFIX)ar

# Flags for compilation
CFLAGS := -v -O2

.PHONY : all
all : libgccmem.o
	$(AR) -rcs libgccmem.a libgccmem.o

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : install
install :
	install libgccmem.h $(INSTALL_INC_DIR)/libgccmem.h
	install libgccmem.a $(INSTALL_LIB_DIR)/libgccmem.a

.PHONY : clean
clean :
	rm -rfv libgccmem.a libgccmem.o
