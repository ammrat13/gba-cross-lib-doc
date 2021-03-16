/**
    aeabi_mem_movement.c
    By: Ammar Ratnani

    Required by the ARM ABI. CLang will assume the ARM ABI is satisfied and will
    try to use these functions unless `-fno-builtins` is passed. This file only
    handles Section 4.3.4 of the ABI dealing with "Memory Copying, Clearing, and
    Setting." See the ARM documentation for more details:
    https://developer.arm.com/documentation/ihi0043/d.

    Note that all the functions are in THUMB mode for efficiency. Make sure to
    compile with `-mthumb-interwork` so calls to these work as expected.
*/

#include "mem.h"


// Check for C++
#ifdef __cplusplus
extern "C" {
#endif


__attribute__((target("thumb")))
void __aeabi_memcpy(void *dest, const void *src, size_t n) {

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
}


__attribute__((target("thumb")))
void __aeabi_memmove(void *dest, const void *src, size_t n) {

    // Again, use `char *` instead of `void *` so we can assign
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
}


__attribute__((target("thumb")))
void __aeabi_memset(void *s, size_t n, int c) {

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
}


__attribute__((target("thumb")))
void __aeabi_memclr(void *s, size_t n) {
    // Chain to `__aeabi_memset`
    __aeabi_memset(s, n, 0);
}


#ifdef __cplusplus
} // extern "C"
#endif
