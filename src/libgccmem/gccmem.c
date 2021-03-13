/**
    libgccmem.c
    By: Ammar Ratnani

    Required to run LibGCC. Even in freestanding mode, the compiler is allowed
    to assume that `memcmp`, `memset`, `memcpy`, and `memmove` exist, so we
    must provide definitions. See their appropriate `man` pages for more detail.

    Note that all the functions are in THUMB mode for efficiency. Make sure to
    compile with `-mthumb-interwork` so calls to these work as expected.
*/

#include "gccmem.h"


// Check for C++
#ifdef __cplusplus
extern "C" {
#endif


__attribute__((target("thumb")))
int memcmp(const void *p1, const void *p2, size_t num) {

    // Compare at most `num` characters before breaking
    for(; num > 0; num--) {

        // Treat the `void *`s as `unsigned char *` and compare
        // We use `unsigned char` instead of `char` because the `man` page
        //  says so
        unsigned char c1 = *((unsigned char *) p1);
        unsigned char c2 = *((unsigned char *) p2);
        if(c1 - c2 != 0)
            return c1 - c2;

        // Don't forget to increment the pointers too
        p1++;
        p2++;
    }

    // If they are equal in the first `num` bytes, consider them equal
    return 0;
}


__attribute__((target("thumb")))
void *memset(void *p, int x, size_t num) {

    // Note that, even though `x` is passed as an integer, we fill with the
    //  result of it being casted to an `unsigned char`. This behavior isn't
    //  documented in the `man` pages.
    // See: http://www.cplusplus.com/reference/cstring/memset/

    // We can't assign to `void *`, so cast to the appropriate type
    unsigned char *rp = (unsigned char *) p;

    // Modify exactly `num` `char`s
    for(; num > 0; num--) {
        // Assign and increment
        *rp = (unsigned char) x;
        rp++;
    }

    // The `man` page says to return a pointer to the start of the changed
    //  memory, and we never changed `p`, so we can use that
    return p;
}


__attribute__((target("thumb")))
void *memcpy(void *dst, const void *src, size_t num) {

    // We can't assign or dereference `void *`, so use a `char *` instead
    const char *rsrc = (const char *) src;
    char *rdst = (char *) dst;

    // Copy exactly `num` `char`s
    for(; num > 0; num--) {
        // Do the copy then increment both pointers
        *rdst = *rsrc;
        rsrc++;
        rdst++;
    }

    // We have to return what was passed in as `dst`, but we never changed it
    return dst;
}


__attribute__((target("thumb")))
void *memmove(void *dst, const void *src, size_t num) {

    // Again, use `char *` instead of `void *` se we can assign
    const char *rsrc = (const char *) src;
    char *rdst = (char *) dst;

    // If the memory regions overlap, copy going up if src > dst and copy going
    //  down if src < dst
    // If the regions don't overlap, the result of the comparison is undefined,
    //  but that's okay since we can copy in any direction
    unsigned char copyDir = 1;
    if(src < dst) {
        copyDir = -1;
        rsrc += num-1;
        rdst += num-1;
    }

    // Actually do the copy
    for(; num > 0; num--) {
        *rdst = *rsrc;
        rsrc += copyDir;
        rdst += copyDir;
    }

    // Return what was passed in as `dst`, but we never changed it
    return dst;
}


#ifdef __cplusplus
} // extern "C"
#endif
