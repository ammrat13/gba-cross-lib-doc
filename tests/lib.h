/*
    lib.h
    By: Ammar Ratnani

    This file includes all the libraries we need in this project. It has stdio,
    stdint, cmocka, and mGBA. It also includes our own libraries.
*/

#ifndef LIB_H
#define LIB_H

#ifdef __cplusplus
extern "C" {
#endif


// Standard libraries
#include <stdio.h>
#include <stdint.h>

// cmocka and its dependencies
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

// mGBA
#include <mgba/core/core.h>


// Our own libraries
#include "utils/silent_log.h"
#include "utils/gba_test_core.h"


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef LIB_H
