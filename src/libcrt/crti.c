/*
    crti.c
    By: Ammar Ratnani

    This file defines a single function that handles the initialization of the
    program. Moves the contents of the `.data` section to where it's supposed
    to be, handles zeroing out the `.bss` section, and calls all the
    constructors. It relies heavily on symbols exported by the linker script.

    Again, these functions are all in THUMB for optimization. Account for that.
*/

#include <mem.h> // For memcpy(), memset(), and size_t
#include "crt.h"

// Prevent name mangling
#ifdef __cplusplus
extern "C" {
#endif


// These symbols were defined in the linker script
// Remember that the way linker symbols work is weird. The symbol holds an
//  address, but accessing that symbol from C automatically dereferences it.
//  Thus, we decleare them as the type of the value they are pointing to, then
//  take the `&` of them.

// For copying over .data
extern char __data_vma_stt;
extern char __data_vma_end;
extern char __data_lma;

// For zeroing out .bss
extern char __bss_vma_stt;
extern char __bss_vma_end;

// For calling constructors
extern void (*__init_arr_stt)(void);
extern void (*__init_arr_end)(void);


__attribute__((target("thumb")))
void _init(void) {

    // Copy over the .data section using memcpy
    // Do pointer arithmetic to get the size of the section
    memcpy(
        &__data_vma_stt,
        &__data_lma,
        (size_t) (&__data_vma_end - &__data_vma_stt)
    );

    // Zero out the .bss section
    // This isn't strictly needed since the BIOS does it for us, but do it
    //  anyway, just in case
    memset(
        &__bss_vma_stt,
        0,
        (size_t) (&__bss_vma_end - &__bss_vma_stt)
    );

    // Call all the constructors
    // Remember that the `_end` symbol points to the first element past the end
    for(void (**f)(void) = &__init_arr_stt; f != &__init_arr_end; f++) {
        (**f)();
    }
}


#ifdef __cplusplus
} // extern "C"
#endif
