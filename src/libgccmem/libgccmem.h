/*
    libgccmem.h
    By: Ammar Ratnani

    A header containing declarations of all the functions LibGCC needs to run.
    Again, all the functions are in THUMB mode for efficiency, so be sure to
    compile with `-mthumb-interwork`.
*/

#ifndef LIBGCCMEM_H
#define LIBGCCMEM_H

// The functions don't require C++, so don't name mangle them
#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h> // For size_t

__attribute__((target("thumb"))) int memcmp(const void *p1, const void *p2, size_t num);
__attribute__((target("thumb"))) void *memset(void *p, int x, size_t num);
__attribute__((target("thumb"))) void *memcpy(void *dst, const void *src, size_t num);
__attribute__((target("thumb"))) void *memmove(void *dst, const void *src, size_t num);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef LIBGCCMEM_H
