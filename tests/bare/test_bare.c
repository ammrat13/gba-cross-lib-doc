/**
    test_bare.c
    By: Ammar Ratnani

    Currently, it will always pass.
*/

#include "runner.h"


// A test that always passes
static int always_pass(void **state) {

}


// The suite to run
static const struct CMUnitTest suite[] = {
    cmocka_unit_test(always_pass),
};
// Run the tests
int run_bare(void) {
    return cmocka_run_group_tests_name("bare", suite, NULL, NULL);
}
