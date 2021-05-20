/*
    placement.h
    By: Ammar Ratnani

    This header defines utility macros for placing variables in particular
    sections of memory.
*/

#ifndef PLACEMENT_H
#define PLACEMENT_H


// Utility macros for string manipulation
// See: https://stackoverflow.com/questions/5459868/concatenate-int-to-string-using-c-preprocessor/5459929
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)


// The identifier we use for the sections
#define SECTION_ID STR(__COUNTER__) "." STR(__LINE__) "." __FILE__

// The actual section macros
#define IDATA __attribute__((section(".iwram_data." SECTION_ID)))
#define IZERO __attribute__((section(".iwram_bss."  SECTION_ID)))
#define EDATA __attribute__((section(".ewram_data." SECTION_ID)))
#define EZERO __attribute__((section(".ewram_bss."  SECTION_ID)))


#endif // ndef PLACEMENT_H
