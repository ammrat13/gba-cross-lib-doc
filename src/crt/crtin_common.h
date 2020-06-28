/*
    crtin_common.h
    By: Ammar Ratnani

    This file contains the functions used by both `crti` and `crtn`. Most
    prominent is perhaps the one that calls a table of function pointers
    given the table's start and length.
*/

#ifndef CRTIN_COMMON_H
#define CRTIN_COMMON_H

#include <stddef.h> // For size_t

#ifdef __cplusplus
extern "C" {
#endif


__attribute__((target("thumb"))) void _call_func_table(void (*tab[])(void), size_t len);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef CRTIN_COMMON_H
