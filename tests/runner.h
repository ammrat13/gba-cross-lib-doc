/**
    runner.h
    By: Ammar Ratnani

    A header file for the main test runner. It has forward declarations of all
    the functions returning suites, as well as a null-terminated list of all of
    them for `main` to iterate over. It also includes the Check header.
*/

#ifndef RUNNER_H
#define RUNNER_H

#ifdef __cplusplus
extern "C" {
#endif


// Include Check
#include <check.h>


// A null-terminated list of all the functions
// Defined in `runner.c`
extern Suite *(*SUITE_FUNCS[])(void);

// Forward declarations of all the test suite functions
Suite *suite_bare(void);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef RUNNER_H
