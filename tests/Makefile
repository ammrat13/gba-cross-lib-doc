# Makefile for Testing
# By: Ammar Ratnani
#
# This file will compile all the tests in this directory. It will produce a
# statically linked binary that can be run on a base system.

# Sensitive to these environment variables
PREFIX ?= $(HOME)/gba-cross-lib-doc
HOST ?= x86_64-pc-linux-gnu-
TARGET ?= arm-agb-eabi-
#HOST_PROGRAM_PREFIX ?= ""
#TARGET_PROGRAM_PREFIX ?= ""

# Get the locations for all the programs
HOST_CC := $(HOST_PROGRAM_PREFIX)$(HOST)gcc
TARGET_CC := $(TARGET_PROGRAM_PREFIX)$(TARGET)gcc
# As well as locations for auxilary files
SPECS := -specs=$(PREFIX)/aux-files/specs
LNKSCRIPT := -T$(PREFIX)/aux-files/lnkscript

# Flags for compilation and linking and the host
HOST_CFLAGS := -v -O2 -g
HOST_LDFLAGS := -v -g
HOST_LDLIBS := -lcheck -lmgba
HOST_INC := -I$(shell pwd)
# Flags for compilation and linking and the target
TARGET_CFLAGS := -v -O2
TARGET_LIB := -L$(PREFIX)/lib
TARGET_INC := -I$(PREFIX)/include

# Files to build
OBJFILES := runner.ho \
	bare/test_bare.ho
GBAFILES := \
	bare/game_bare.to
# The name of out output executable
OUTFILE := tests.out


# Do the linking at the very end
.PHONY : all
all : $(OBJFILES) $(GBAFILES)
	$(HOST_CC) $(HOST_LDFLAGS) -o $(OUTFILE) $(OBJFILES) $(HOST_LDLIBS)

# Rule for host code
%.ho : %.c
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_INC) -c -o $@ $<

# Rule for target code
%.to : %.c
	$(TARGET_CC) $(SPECS) $(LNKSCRIPT) \
		$(TARGET_CFLAGS) $(TARGET_LIB) $(TARGET_INC) -o $@ $<

# Rule to clean
.PHONY : clean
clean :
	find . -type f -name '*.ho' -delete -print
	find . -type f -name '*.to' -delete -print
	rm -rfv *.out
