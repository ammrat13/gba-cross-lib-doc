# Makefile for All the Libraries
# By: Ammar Ratnani
#
# This file is provided for convinience purposes. It will essentially run a
# specified target on all the subdirectories. It will handle dependencies as
# well.
#
# See: https://stackoverflow.com/questions/17834582/run-make-in-each-subdirectory/17845120

# Targets we support
TARGETS := all install clean
# Directories we will use
DIRECTORIES := libstrmacro libplacement libmem libcrt

# Mark the targets as phony
.PHONY: $(TARGETS) $(DIRECTORIES)
# Set the targets to require all subdirs
$(TARGETS): $(DIRECTORIES)

# Generic do in directory
$(DIRECTORIES):
	$(MAKE) -C $@ $(MAKECMDGOALS)

# Special ordering for compile-time dependencies
libcrt: libmem
