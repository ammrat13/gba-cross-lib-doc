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


__attribute__((target("thumb")))
void *memset(void *s, int c, size_t n) {

    // Note that, even though `c` is passed as an integer, we fill with the
    //  result of it being casted to an `unsigned char`. This behavior isn't
    //  documented in the `man` pages.
    // See: http://www.cplusplus.com/reference/cstring/memset/

    // We can't assign to `void *`, so cast to the appropriate type
    unsigned char *rs = (unsigned char *) s;

    // Modify exactly `n` `char`s
    for(; n > 0; n--) {
        // Assign and increment
        *rs = (unsigned char) c;
        rs++;
    }

    // The `man` page says to return a pointer to the start of the changed
    //  memory, and we never changed `s`, so we can use that
    return s;
}


__attribute__((target("thumb")))
void *memcpy(void *dest, const void *src, size_t n) {

    // We can't assign or dereference `void *`, so use a `char *` instead
    const char *rsrc = (const char *) src;
    char *rdest = (char *) dest;

    // Copy exactly `n` `char`s
    for(; n > 0; n--) {
        // Do the copy then increment both pointers
        *rdest = *rsrc;
        rsrc++;
        rdest++;
    }

    // We have to return what was passed in as `dest`, but we never changed it
    return dest;
}


__attribute__((target("thumb")))
void *memmove(void *dest, const void *src, size_t n) {

    // Again, use `char *` instead of `void *` se we can assign
    const char *rsrc = (const char *) src;
    char *rdest = (char *) dest;

    // If the memory regions overlap, copy going up if src > dest and copy going
    //  down if src < dest
    // If the regions don't overlap, the result of the comparison is undefined,
    //  but that's okay since we can copy in any direction
    unsigned char copyDir = 1;
    if(src < dest) {
        copyDir = -1;
        rsrc += n-1;
        rdest += n-1;
    }

    // Actually do the copy
    for(; n > 0; n--) {
        *rdest = *rsrc;
        rsrc += copyDir;
        rdest += copyDir;
    }

    // Return what was passed in as `dest`, but we never changed it
    return dest;
}


#ifdef __cplusplus
} // extern "C"
#endif
