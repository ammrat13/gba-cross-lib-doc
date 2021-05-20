/**
    runner.c
    By: Ammar Ratnani

    Implementation file for running the tests. It will simply create a group
    test from all the `TEST_CASES` and run it.
*/

// Runner header
#include "runner.h"


int main(void) {

    // Disable mGBA logging to STDOUT
    mLogSetDefaultLogger(&silent_logger);

    // Run the tests
    // Need to declare it inside main because can't initialize outside
    const struct CMUnitTest TEST_CASES[] = {
        cmtest_bare,
        cmtest_memory_placement,
    };
    return cmocka_run_group_tests(TEST_CASES, NULL, NULL);
}
