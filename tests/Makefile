# Makefile for Testing
# By: Ammar Ratnani
#
# This file will compile all the tests in this directory. It will produce a
# statically linked binary that can be run on a base system.

# Sensitive to these environment variables
PREFIX ?= $(HOME)/gba-cross-lib-doc
HOST ?= x86_64-pc-linux-gnu-
TARGET ?= arm-agb-eabi-
#HOST_PROGRAM_PREFIX ?=
#TARGET_PROGRAM_PREFIX ?=
#CI ?=


# Get the root directory of this makefile
# See: https://stackoverflow.com/questions/18136918/how-to-get-current-relative-directory-of-your-makefile
ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

# Get the locations for all the programs
HOST_CC := $(HOST_PROGRAM_PREFIX)$(HOST)gcc
TARGET_CC := $(TARGET_PROGRAM_PREFIX)$(TARGET)gcc
TARGET_OBJCOPY := $(TARGET_PROGRAM_PREFIX)$(TARGET)objcopy
# As well as locations for auxilary files
SPECS := -specs=$(PREFIX)/aux-files/specs
LNKSCRIPT := -T$(PREFIX)/aux-files/lnkscript

# Flags for compilation and linking and the host
# Some extra defines are needed to compile mGBA headers
HOST_CFLAGS := -v -g -O2 -Wall -Werror
HOST_CDEFS := -DM_CORE_GBA -DMGBA_STANDALONE -UCOLOR_16_BIT
HOST_LDFLAGS := -v
HOST_LDLIBS := -lcmocka -lmgba
HOST_INC := -I$(ROOT_DIR)/
# Flags for compilation and linking and the target
TARGET_CFLAGS := -v -O2 -Wall -Werror
TARGET_LIB := -L$(PREFIX)/lib
TARGET_INC := -I$(PREFIX)/include

# Files to build
OBJFILES := runner.hobj utils/silent_log.hobj utils/gba_test_core.hobj \
	tests/bare_test.hobj
GBAFILES := \
	tests/bare_game.thex
# The name of out output executable
OUTFILE := tests.out


# Don't delete `.tobj` files
.SECONDARY :

# Do the linking at the very end
.PHONY : all
all : $(OBJFILES) $(GBAFILES)
	$(HOST_CC) $(HOST_LDFLAGS) -o $(OUTFILE) $(OBJFILES) $(HOST_LDLIBS)

# Rule for host code
%.hobj : %.c
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_CDEFS) $(HOST_INC) -c -o $@ $<

# Rule for target code
%.thex : %.tobj
	$(TARGET_OBJCOPY) -O binary $< $@
%.tobj : %.c
	$(TARGET_CC) $(SPECS) $(LNKSCRIPT) \
		$(TARGET_CFLAGS) $(TARGET_LIB) $(TARGET_INC) -o $@ $<

# Rule to clean
.PHONY : clean
clean :
	find . -type f -name '*.hobj' -delete -print
	find . -type f -name '*.tobj' -delete -print
	find . -type f -name '*.thex' -delete -print
	rm -rfv *.out
