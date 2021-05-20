/**
    runner.h
    By: Ammar Ratnani

    A header file for the main test runner. It has forward declarations for all
    the `CMUnitTest`s to run. Note that these tests must be added to the *local*
    variable `TEST_CASES` in `runner.c`. This header includes `lib.h`.
*/

#ifndef RUNNER_H
#define RUNNER_H

#ifdef __cplusplus
extern "C" {
#endif


// Include libraries
#include "lib.h"


// Forward declarations of all the unit tests to run
extern const struct CMUnitTest cmtest_bare;
extern const struct CMUnitTest cmtest_memory_placement;


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef RUNNER_H
