# Makefile for LibPlacement
# By: Ammar Ratnani
#
# This file just installs the header.

# Sensitive to these environment variables
PREFIX ?= $(HOME)/gba-cross-lib-doc

# Where to install
INSTALL_INC_DIR := $(PREFIX)/include/
# What to install
INCFILES := placement.h


# All and clean don't need to do anything
.PHONY : all clean
all : ;
clean : ;

# Install the file on install
install : all
	install -D -t $(INSTALL_INC_DIR) $(INCFILES)
