/**
    runner.h
    By: Ammar Ratnani

    A header file for the main test runner. It has forward declarations for all
    the group test functions to call for unit testing, as well as a declaration
    for a null-terminated array of all of them. This header also includes cmocka
    (and its required headers) and stdio.
*/

#ifndef RUNNER_H
#define RUNNER_H

#ifdef __cplusplus
extern "C" {
#endif


// Include libraries
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


// Functions that run `cmocka_run_group_tests`
// Should return the result of that call - the number of failed tests
typedef int group_test_run_t(void);

// Forward declarations of all the group test functions
extern group_test_run_t run_bare;

// A null-terminated list of all those functions
// Defined in `runner.c`
extern group_test_run_t *GROUP_TEST_RUNS[];


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef RUNNER_H
