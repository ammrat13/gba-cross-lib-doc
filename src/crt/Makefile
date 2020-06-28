# Makefile for CRT Files
# By: Ammar Ratnani
#
# This file just assembles all the specified files and installs them into the 
# appropriate directory. It could be reused elsewhere if needed.

# Sensitive to these environment variables
PREFIX ?= $(HOME)/gba-cross-lib-doc
TARGET ?= arm-agb-eabi

# Find where everything is and where to install
PROGRAM_DIR := $(PREFIX)/toolchain/bin
INSTALL_DIR := $(PREFIX)/lib

# Get the locations for all the programs
PROGRAM_PREFIX := $(PROGRAM_DIR)/$(TARGET)-
CC := $(PROGRAM_PREFIX)gcc

# Flags for compilation
CFLAGS := -v -O2

# Files to build
OBJFILES := crt0.o crti.o

.PHONY : all
all : $(OBJFILES)

%.o : %.s
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : install
install :
	install -t $(INSTALL_DIR) $(OBJFILES)

.PHONY : clean
clean :
	rm -rfv $(OBJFILES)
