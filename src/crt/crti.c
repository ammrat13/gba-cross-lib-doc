/*
    crti.c
    By: Ammar Ratnani

    This file defines a single function that handles the initialization of the
    program. It calls all the constructors in `.init_array`, relying on symbols
    exported by the linker.
*/


// These symbols were defined in the linker script
// They are pointers to function pointers (2 indirections), but they are also
//  pure symbols, so we need to take the address of these symbols to get to 
//  the actual value. Declaring them as function pointers (1 indirection) makes
//  the typing work
extern void (*__init_arr_stt)(void);
extern void (*__init_arr_end)(void);

void _init(void) {
    // Iterate through the array, calling all the functions
    // Remember that we set the end to be just past the last element
    for(void (**f)(void) = &__init_arr_stt; f != &__init_arr_end; f++) {
        (**f)();
    }
}
