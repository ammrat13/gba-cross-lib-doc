# Makefile for CRT Files
# By: Ammar Ratnani
#
# This file just assembles all the specified files and installs them into the
# appropriate directory. It could be reused elsewhere if needed.

# Sensitive to these environment variables
PREFIX ?= $(HOME)/gba-cross-lib-doc
TARGET ?= arm-agb-eabi
#PROGRAM_PREFIX ?= ""

# Where to install
INSTALL_LIB_DIR := $(PREFIX)/lib
INSTALL_INC_DIR := $(PREFIX)/include

# Get all the programs
CC := $(PROGRAM_PREFIX)$(TARGET)-gcc

# Flags for compilation and linking
CFLAGS := -v -O2

# Files to include and build
INCFILES := crt.h
OBJFILES := crt0.o crti.o


.PHONY : all
all : $(OBJFILES)

# Specify two ways to compile object files - one from assembly and one from C
%.o : %.s
	$(CC) $(CFLAGS) -c -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : install
install : all
	install -D -t $(INSTALL_INC_DIR) $(INCFILES)
	install -D -t $(INSTALL_LIB_DIR) $(OBJFILES)

.PHONY : clean
clean :
	rm -rfv *.o
