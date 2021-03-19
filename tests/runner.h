/**
    runner.h
    By: Ammar Ratnani

    A header file for the main test runner. It has forward declarations of all
    the functions returning suites, as well as a null-terminated list of all of
    them for `main` to iterate over. It also includes Check and stdio. Finally,
    it has convinience macros for writing tests.
*/

#ifndef RUNNER_H
#define RUNNER_H

#ifdef __cplusplus
extern "C" {
#endif


// Include libraries
#include <stdio.h>
#include <check.h>

// Defines name##_printed which holds whether the current file's name has been
//  printed as a comment for TAP
// Also defines name##_print to print the TAP comment if it hasn't already
#define INIT_FILE(name) \
    static int name##_printed = 0; \
    static void name##_print(void) { \
        if(!name##_printed) { \
            printf("# %s\n", #name); \
        } \
        name##_printed = 1; \
    } \


// A null-terminated list of all the functions
// Defined in `runner.c`
extern Suite *(*SUITE_FUNCS[])(void);

// Forward declarations of all the test suite functions
Suite *suite_bare(void);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef RUNNER_H
