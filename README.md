# GBA Cross Compiling Libraries
This repository serves both as documentation and as a library for building GCC
to cross compile to the GBA. At the moment, it's quite minimal. It only supports
C and Assembly, it doesn't support constructors or destructors, and it doesn't
even have a C standard library. Nonetheless, it can compile simple games, such
as the ones developed in Georgia Tech's CS 2110.


## Directory Structure
The directory structure I used when making this library and that I wrote the
Makefiles to use is as follows. This repository is put alongside the
subdirectories
 * `compiler`: the directory into which cross-`binutils` and cross-`gcc` are
               (to be) installed
 * `debugger`: the directory into which cross-`gdb` is (to be) installed
 * `include`: headers for C programs (currently empty)
 * `lib`: libraries for C programs to link against
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
the root source folder, so make a subdirectory and `cd` into it. Then 
```
$ ../configure \
    --prefix=$PREFIX/compiler --target=$TARGET --program-prefix=$TARGET- \
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
    --prefix=$PREFIX/compiler --target=$TARGET --program-prefix=$TARGET- \
    --with-march=armv4t --enable-languages=c --without-headers --disable-nls \
    --with-system-zlib --enable-lto --disable-threads \
    --enable-interwork --enable-nofmult \
    --disable-fpu --disable-26bit --disable-biendian --disable-underscore
$ make all-gcc && make install-gcc
$ make all-target-libgcc && make install-target-libgcc
```
This will install a minimal version of GCC, containing not much more than the
compiler and LibGCC, which is required to correctly run the compiler.
Alternatively, you can simply `make && make install` after configuring with
```
...
    --disable-libsanitizer --disable-libssp --disable-libquadmath --disable-libvtv \
...
```
This will also produce a minimal installation but one that includes LibCC1,
which is (presumably) required for GDB integration with `-g`.

### GDB
Change into the source directory, make a build directory, and `cd` into it. Then
```
$ ../configure \
    --prefix=$PREFIX/debugger --target=$TARGET --program-prefix=$TARGET- \
    --enable-languages=c --with-system-zlib \
    --disable-libquadmath --disable-libstdcxx
$ make && make install
```

