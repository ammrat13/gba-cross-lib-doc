/*
    placement.h
    By: Ammar Ratnani

    This header defines utility macros for placing variables in particular
    sections of memory.
*/

#ifndef PLACEMENT_H
#define PLACEMENT_H


// Needed for string utility functions in macros
#include <util/str_macro.h>


// The identifier we use for the sections
#define SECTION_ID STR(__COUNTER__) "." STR(__LINE__) "." __FILE__

// The actual section macros
#define IDATA __attribute__((section(".iwram_data." SECTION_ID)))
#define IZERO __attribute__((section(".iwram_bss."  SECTION_ID)))
#define EDATA __attribute__((section(".ewram_data." SECTION_ID)))
#define EZERO __attribute__((section(".ewram_bss."  SECTION_ID)))


#endif // ndef PLACEMENT_H
