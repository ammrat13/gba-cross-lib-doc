# GBA Toolchain Tests Source

This directory contains the source code for the tests on the GBA toolchain and
libraries. It relies on mGBA for emulation and cmocka for its testing framework.
Output can be controlled with cmocka's environment variables - see their
[API](https://api.cmocka.org/).

Right now the suite is very simple. It just has one test that the toolchain can
produce a game that can display something.


## Variables

The compilation is expected to happen inside the Docker container. It is
sensitive to the following variables:
* `PREFIX`: The root of the GBA toolchain. Set to `/gba-lib/`.
* `HOST`: The program prefix of the host compiler, with the trailing dash. Set
  to empty.
* `TARGET`: The program prefix of the cross compiler, with the trailing dash.
  Set to `arm-none-eabi-`.
* `HOST_PROGRAM_PREFIX`: The directory in which the host compiler resides.
  Default is empty.
* `TARGET_PROGRAM_PREFIX`: The directory in which the cross compiler resides.
  Default is empty.
* `SPECS`: The option to set the GCC specs file during cross compilation. Set to
  `-specs=${PREFIX}/aux-files/specs`
* `LNKSCRIPT`: The option to set the linker script during cross compilation. Set
  to `-T${PREFIX}/aux-files/lnkscript`


## Workflow

A test consists of a pair of files: one to run emulated on the GBA and one to
run on the host to verify that it ran correctly. The host code will be compiled
to a `.hobj` (host object) file then linked into the output executable. The
target code will be compiled and linked into a `.tobj` (target object) file,
copied into a `.thex` (target hex) file, then loaded into the emulated GBA by
its corresponding `.hobj` file.

Note that the target code is compiled and linked in one step. Thus, the C files
with GBA code must be self-contained, except for existing libraries.

To add a test, create the host and target C files, add them to the `Makefile`,
then register the host code with `runner.c` by adding the function to run all
the tests to `GROUP_TEST_RUNS`.
