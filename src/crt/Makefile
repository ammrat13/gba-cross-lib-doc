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
LD := $(PROGRAM_PREFIX)ld

# Flags for compilation and linking
CFLAGS := -v -O2
LDFLAGS := -r

# Files to build
OBJFILES := crt0.o crti.o

.PHONY : all
all : $(OBJFILES)


# Override the compilation for crti because we have to link
crti.o : crti.c crtin_common.o
	$(CC) $(CFLAGS) -c -o crti_specialized.o crti.c
	$(LD) $(LDFLAGS) -o crti.o crti_specialized.o crtin_common.o

# Specify two ways to compile object files - one from assembly and one from C
%.o : %.s
	$(CC) $(CFLAGS) -c -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY : install
install : all
	install -t $(INSTALL_DIR) $(OBJFILES)

.PHONY : clean
clean :
	rm -rfv *.o
