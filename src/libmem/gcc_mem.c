/**
    gcc_mem.c
    By: Ammar Ratnani

    Required to run GCC. Even in freestanding mode, the compiler is allowed to
    assume that `memcmp`, `memset`, `memcpy`, and `memmove` exist, so we must
    provide definitions. See their appropriate `man` pages for more detail.

    Note that all the functions are in THUMB mode for efficiency. Make sure to
    compile with `-mthumb-interwork` so calls to these work as expected.
*/

#include "mem.h"


// Check for C++
#ifdef __cplusplus
extern "C" {
#endif


__attribute__((target("thumb")))
int memcmp(const void *s1, const void *s2, size_t n) {

    // Compare at most `n` characters before breaking
    for(; n > 0; n--) {

        // Treat the `void *`s as `unsigned char *` and compare
        // We use `unsigned char` instead of `char` because the `man` page
        //  says so
        unsigned char c1 = *((unsigned char *) s1);
        unsigned char c2 = *((unsigned char *) s2);
        if(c1 - c2 != 0)
            return c1 - c2;

        // Don't forget to increment the pointers too
        s1++;
        s2++;
    }

    // If they are equal in the first `num` bytes, consider them equal
    return 0;
}


/*
    For the rest of the functions, we just chain to `aeabi_mem_movement`. The
    ABI functions do more or less the same thing, and this prevents code
    duplication. We just need to be mindful of the return value.
*/

__attribute__((target("thumb")))
void *memset(void *s, int c, size_t n) {
    // Chain the call
    // Mind the ordering of the parameters
    __aeabi_memset(s, n, c);
    // The `man` page says to return a pointer to the start of the changed
    //  memory, and we never changed `s`, so we can use that
    return s;
}

__attribute__((target("thumb")))
void *memcpy(void *dest, const void *src, size_t n) {
    // Chain the call
    __aeabi_memcpy(dest, src, n);
    // Return what was passed in `dest`
    return dest;
}

__attribute__((target("thumb")))
void *memmove(void *dest, const void *src, size_t n) {
    // Chain the call
    __aeabi_memmove(dest, src, n);
    // Return what was passed in `dest`
    return dest;
}


#ifdef __cplusplus
} // extern "C"
#endif
