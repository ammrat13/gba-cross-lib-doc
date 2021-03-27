/**
    runner.c
    By: Ammar Ratnani

    Implementation file for running the tests. It simply loops over
    `GROUP_TEST_RUNS` and runs all the groups.
*/

// Runner header
#include "runner.h"

// Needed for logging
#include "utils/silent_log.h"


group_test_run_t *GROUP_TEST_RUNS[] = {
    run_bare,
    NULL,
};


int main(void) {

    // Disable mGBA logging to STDOUT
    mLogSetDefaultLogger(&silent_logger);

    // Keep track of how many failures we've had
    int failures = 0;

    // Loop over all the group test functions
    // Remember that the array is terminated by a null, and will therefore
    //  always have at least one element.
    for(group_test_run_t **gtr = GROUP_TEST_RUNS; *gtr != NULL; gtr++) {
        // Track the failures
        failures += (*gtr)();
    }

    // Return the number of failures
    return failures;
}
