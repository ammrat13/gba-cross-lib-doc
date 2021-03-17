# Makefile for All the Libraries
# By: Ammar Ratnani
#
# This file is provided for convinience purposes. It will essentiall run a
# specified target on `libmem` and `libcrt`. It will do `libmem` first due to
# dependencies.
#
# See: https://stackoverflow.com/questions/17834582/run-make-in-each-subdirectory/17845120

# Targets we support
TARGETS := all install clean
# Directories we will use
DIRECTORIES := libmem libcrt

# Mark the targets as phony
.PHONY: $(TARGETS) $(DIRECTORIES)
# Set the targets to require all subdirs
$(TARGETS): $(DIRECTORIES)

# Generic do in directory
$(DIRECTORIES):
	$(MAKE) -C $@ $(MAKECMDGOALS)

# Special ordering for dependencies
libcrt: libmem
