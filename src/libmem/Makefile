# Makefile for LibMem
# By: Ammar Ratnani
#
# This file will simply compile the files in this library, turn them into an
# archive for linking, then move it to the right place.

# Sensitive to these environment variables
PREFIX ?= $(HOME)/gba-cross-lib-doc
TARGET ?= arm-agb-eabi
#PROGRAM_PREFIX ?= ""

# Where to install
INSTALL_LIB_DIR := $(PREFIX)/lib
INSTALL_INC_DIR := $(PREFIX)/include

# Get the locations for all the programs
CC := $(PROGRAM_PREFIX)$(TARGET)-gcc
AR := $(PROGRAM_PREFIX)$(TARGET)-ar

# Flags for compilation
# We say no builtins because we're implementing them
CFLAGS := -fno-builtin -ffunction-sections -v -O2

# Files to include and build
INCFILES := mem.h
OBJFILES := gcc_mem.o
# The final name of the archive
ARFILE := libmem.a


.PHONY : all
all : $(OBJFILES)
	$(AR) -rcs $(ARFILE) $(OBJFILES)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : install
install : all
	install -D -t $(INSTALL_INC_DIR) $(INCFILES)
	install -D -t $(INSTALL_LIB_DIR) $(ARFILE)

.PHONY : clean
clean :
	rm -rfv *.a *.o
