# GBA Toolchain

This image is to be used for GBA cross compilation. It is derived from the GBA
Base image, and therefore has the required toolchain installed.

The `Dockerfile` just installs the (custom) runtime libraries needed. It
installs everything in the `src/` and `aux-files/` subdirectories of the
repository.

It also sets up the default command for building games. It assumes the source
tree is mounted at `/work/` in the container, and it will run `make` with the
following variable overrides:
* `PREFIX`: The root of the newly installed GBA toolchain. Set to `/gba-lib/`.
* `HOST`: The program prefix of the host compiler, with the trailing dash.
  Set to empty.
* `TARGET`: The program prefix of the cross compiler, with the trailing dash.
  Set to `arm-none-eabi-`.
* `SPECS`: The option to set the GCC specs file during cross compilation. Set to
  `-specs=${PREFIX}/aux-files/specs`
* `LNKSCRIPT`: The option to set the linker script during cross compilation. Set
  to `-T${PREFIX}/aux-files/lnkscript`
