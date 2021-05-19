# GBA Toolchain Source

This directory contains the source code required to get the toolchain to work,
as well as some other utilities. The top-level `Makefile` simply calls those in
the requisite subdirectories in the right order.


## Compilation Notes

***IMPORTANT:*** *We expect that `all` is a prerequisiste for `install`.* That
is, it should be possible to install with `make install` without ever manually
running `make all`. The top level `Makefile` relies on this.

Other than that, the compilation is sensitive to the following variables:
* `PREFIX`: The installation root. Default is `$(HOME)/gba-cross-lib-doc`, and
  set to `/gba-lib/` on the Docker.
* `TARGET`: The program prefix of the cross compiler, with the trailing dash.
  Default is `arm-agb-eabi-` and set to `arm-none-eabi-` on the Docker.
* `TARGET_PROGRAM_PREFIX`: The path to the cross compiler. Default is empty.
* `INSTALL_LIB_DIR`: Where to install libraries. Default is `$(PREFIX)/lib/`
* `INSTALL_INC_DIR`: Where to install headers. Default is `$(PREFIX)/include/`
