/*
    mem.h
    By: Ammar Ratnani

    A header containing declarations of all the memory-related functions in this
    library. Again, all the functions are in THUMB mode for efficiency, so be
    sure to compile with `-mthumb-interwork`.
*/

#ifndef _MEM_H
#define _MEM_H

// The functions don't require C++, so don't name mangle them
#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h> // For size_t

// From `gcc_mem_movement.c`
__attribute__((target("thumb"))) int memcmp(const void *s1, const void *s2, size_t n);
__attribute__((target("thumb"))) void *memset(void *s, int c, size_t n);
__attribute__((target("thumb"))) void *memcpy(void *dest, const void *src, size_t n);
__attribute__((target("thumb"))) void *memmove(void *dest, const void *src, size_t n);

// From `aeabi_mem_movement.c`
__attribute__((target("thumb"))) void __aeabi_memcpy(void *dest, const void *src, size_t n);
__attribute__((target("thumb"))) void __aeabi_memmove(void *dest, const void *src, size_t n);
__attribute__((target("thumb"))) void __aeabi_memset(void *s, size_t n, int c);
__attribute__((target("thumb"))) void __aeabi_memclr(void *s, size_t n);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef _MEM_H
