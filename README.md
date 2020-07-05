# GBA Cross Compiling: Libraries and Documentation
This repository serves both as documentation and as a library for building GCC
to cross compile to the GBA. At the moment, the library is quite minimal. It
only supports Assembly, C, and very basic C++, and it doesn't have a `malloc` or
even a standard library. Nonetheless, it can compile simple games, such as the
ones developed in Georgia Tech's CS 2110.


## Directory Structure
The directory structure that I used when making this library and that I wrote
the Makefiles to use is as follows. This repository is put in `$PREFIX`
alongside the following subdirectories:
 * `toolchain`: the directory in which Cross-Binutils, -GCC, and -GDB are (to
                be) installed
 * `lib`: libraries for the GBA, some of which are required for programs to run
          correctly, as well as compiler and linker configuration files
 * `include`: headers declaring the symbols used in the above libraries
 * `src`: the source code of everything in the other directories, including the
          the compiler and debugger


## Compiling the Toolchain
Start by setting the environment variables
```
$ export PREFIX=/path/to/install/dir
$ export TARGET=arm-agb-eabi
```

### Binutils
Change into the source code's directory. It is not recommended to build inside
the root source folder, so make a subdirectory for building and `cd` into it.
Then
```
$ ../configure \
    --prefix=$PREFIX/toolchain --target=$TARGET --program-prefix=$TARGET- \
    --with-system-zlib --with-sysroot --disable-nls \
    --enable-plugins --enable-lto \
    --enable-interwork --enable-nofmult \
    --disable-fpu --disable-26bit --disable-biendian --disable-underscore 
$ make && make install
```

### GCC
Change into the source code's directory, make a build subdirectory, and `cd`
into it. Then
```
$ ../configure \
    --prefix=$PREFIX/toolchain --target=$TARGET --program-prefix=$TARGET- \
    --with-march=armv4t --enable-languages=c,c++ --without-headers \
    --with-system-zlib --enable-lto --disable-threads --disable-nls \
    --enable-interwork --enable-nofmult \
    --disable-fpu --disable-26bit --disable-biendian --disable-underscore
$ make all-gcc && make install-gcc
$ make all-target-libgcc && make install-target-libgcc
```
This will install a minimal version of GCC, containing not much more than the
compiler and LibGCC, which GCC requires to work correctly. Alternatively, you
can simply `make && make install` after configuring with
```
...
    --disable-libsanitizer --disable-libssp --disable-libvtv \
    --disable-libquadmath --disable-libgomp --disable-libstdcxx \
...
```
This will also produce a minimal installation but one that includes LibCC1,
which is (presumably) required for GDB integration with `-g`.

### GDB
Change into the source directory, make a build directory, and `cd` into it. Then
```
$ ../configure \
    --prefix=$PREFIX/toolchain --target=$TARGET --program-prefix=$TARGET- \
    --enable-languages=c,c++ --disable-nls --with-system-zlib \
    --disable-libquadmath --disable-libstdcxx
$ make && make install
```

### Options Used
We have several generic options used by most toolchain components:
 * `prefix`: The directory into which `make` will install the software's
             subdirectory structure. For a global installation, this is usually
             set to `/` or `/usr`
 * `target`: The platform we want the compiled binaries to be able to compile
             and debug for. For instance, we will compile our toochain to run on
             `x86_64-pc-linux-gnu`, but we want to use the toolchain to compile
             for `arm-agb-eabi`, so we set that as our target.
 * `program-prefix`: The string passed into this is prepended to all the
                     binaries installed into `$PREFIX/bin`. For instance, `as`
                     would be renamed `arm-agb-eabi-as`.
 * `with-march`: Sets the compiler to add options to its default `specs` file to
                 target this architecture specifically. Out of the box, It
                 allows the compiler to make optimizations and use instructions
                 specific to this processor, without regard to the code working
                 on others.
 * `enable-languages`: A comma-separated list programming languages the
                       compiler and debugger would need to support. Use `c` for
                       C support and `c++` for C++.
 * `with-sysroot`: When used without a parameter, allows Binutils to later run
                   with a standard system directory, much like `/` or`/usr`.
                   Note that GCC and Binutils must have the same system root.
                   Thus, we don't specify it here as we don't have the system
                   headers GCC needs to support having a system root.
 * `without-headers`: Tells GCC that we don't have standard C library headers
                      for the target architecture, so don't assume their
                      existance. This implies that GCC is compiled without a
                      system root.
 * `disable-nls`: Don't build support for languages other than English.
 * `with-system-zlib`: Many of the toolchain components come with their own
                       versions of ZLib. However, we have it installed on the
                       host system, so there's no reason to rebuild it.
 * `enable-plugins`: Allow us to use plugins for Binutils such as LTO.
 * `enable-lto`: A plugin for Binutils that GCC can take advantage of. Enables
                 link-time optimization.

Additionally, we have a few options regarding what libraries to (not) compile:
 * `libsanitizer`: Used for detecting and dubugging runtime errors such as
                   invalid addresses, memory leaks, and undefined behavior. We
                   have no way to handle these exceptions on the GBA.
 * `libssp`: Used to detect stack smashing attempts, usually due to buffer
             overflows. Presumably, this is responsible for inserting the 
             `**** stack smashing detected ***:` error on hosted systems. It
             requires some additional setup to get working on the GBA.
 * `libvtv`: Is used to validate tables of virtual functions. We won't be able
             to run this on the GBA without additional configuration.
 * `libquadmath`: Allows programs to use 128-bit floats. On the GBA, you
                  shouldn't be using floats anyway.
 * `libgomp`: Allows for parallel processing using OpenMP. The GBA is
              single-threaded and doesn't have OpenMP support.
 * `libstdcxx`: The C++ standard library. Again, we can't run this without more
                configuration since the GBA is an embedded target.

Finally, we gave some options for what parts of MultiLib to compile:
 * `interwork`: The GBA supports both ARM and THUMB machine code. This option
                should enable GCC to generate code to allow us to call one type 
                of assembly language from another.
 * `nofmult`: By default, GCC will be compiled with support for finite-field
              multiplication instructions. The GBA has none of these, so we
              don't need `fmult`.
 * `fpu`: The GBA doesn't have a floating-point unit.
 * `26bit`: Some old ARM processors were 26-bit, and this option would allow us
            to target them. We don't need to, however.
 * `biendian`: The GBA is little-endian, so we don't need to build support for
               both endiannesses.
 * `underscore`: I don't know what it is, but I don't think we need it.


## Post-Compilation
Once the toolchain is installed, you can make several quality-of-life
adjustments:
 * Delete unnecessary directiories. The folder `toolchain/share` contains only
   `man` and `info` pages and can safely be removed. Similarly,
   `toolchain/$TARGET/lib` only has linker scripts, but we provide our own.
 * Point GCC to your `specs` file instead of the built-in one. If available, it
   will use the file named `specs` in the same directory as LibGCC &mdash; in
   `dirname $($PREFIX/toolchain/bin/$TARGET-gcc -print-libgcc-file-name)`.
   Simply symbolic link that file to the `specs` you want.
 * Adjust the `specs` and `Makefile`s to point to your installation directory.
   This way you don't have to create and maintain a `$PREFIX` environment
   variable. In `specs`, change every instance of `%:getenv(PREFIX x)` to be
   your installation directory followed by `x`. In the `Makefile`s, just change
   the default value of `PREFIX`. Also change the other paths if your directory
   structure differs from mine.
 * Install the provided libraries. Note that LibGCCMem and LibCRT are required
   for the toolchain to run correctly. Also note the dependencies between
   libraries:
     * LibCRT must be installed after LibGCCMem

## TODO
 * Write tests for the libraries
 * Increase support for C++
 * Optimize LibGCCMem
 * Add more libraries
 * Write more documentation
