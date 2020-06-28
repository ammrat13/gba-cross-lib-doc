/*
    crtn.c
    By: Ammar Ratnani

    This file defines a single THUMB function to handle ending the program. It
    isn't strictly needed since a hard-reset or a shutdown will do the same
    thing, but it's good practice. It just calls all the destructors.

    It's essentially a stripped down `crti.c`, so look to that for details.
*/

#include "crtin_common.h" // For _call_func_table()

// Prevent name mangling
#ifdef __cplusplus
extern "C" {
#endif


// Linker script symbols for the .fini_array sections
extern void (*__fini_arr_stt)(void);
extern void (*__fini_arr_end)(void);


__attribute__((target("thumb")))
void _fini(void) {
    // Just call the destructors
    _call_func_table(
        &__fini_arr_stt,
        (size_t) (&__fini_arr_end - &__fini_arr_stt)
    );
}


#ifdef __cplusplus
} // extern "C"
#endif
