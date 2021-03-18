# Makefile for Testing
# By: Ammar Ratnani
#
# This file will compile all the tests in this directory. It will produce a
# statically linked binary that can be run on a base system.

# Sensitive to these environment variables
PREFIX ?= $(HOME)/gba-cross-lib-doc
HOST ?= x86_64-pc-linux-gnu
TARGET ?= arm-agb-eabi
#HOST_PROGRAM_PREFIX ?= ""
#TARGET_PROGRAM_PREFIX ?= ""

# Get the locations for all the programs
HOST_CC := $(HOST_PROGRAM_PREFIX)$(HOST)-gcc
TARGET_CC := $(TARGET_PROGRAM_PREFIX)$(TARGET)-gcc
