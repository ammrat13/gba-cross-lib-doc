# LibMem

This library provides the necessary memory functions for the compiler to work.
Even though we compile with `-ffreestanding`, GCC is allowed to assume the
existence of some basic functions. A similar thing is true for Clang, though
only GCC is supported right now.

See [GCC's Manual § 2](http://gcc.gnu.org/onlinedocs/gcc/Standards.html):
> Most of the compiler support routines used by GCC are present in libgcc, but
> there are a few exceptions. GCC requires the freestanding environment provide
> `memcpy`, `memmove`, `memset` and `memcmp`.

The library finally includes a header with all the memory support routines, so
they can be used by normal code.
