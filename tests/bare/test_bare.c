/**
    test_bare.c
    By: Ammar Ratnani

    Currently, it will always pass.
*/

#include "runner.h"

INIT_FILE(bare);


// A test that always passes
START_TEST(do_test) {
    ck_assert_int_eq(0,0);
} END_TEST


// Return the suite to run
Suite *suite_bare(void) {
    // Setup
    Suite *ret = suite_create("bare");
    TCase *cas = tcase_create("do_test");
    tcase_add_unchecked_fixture(cas, bare_print, NULL);

    // Add tests
    tcase_add_test(cas, do_test);

    // Return
    suite_add_tcase(ret, cas);
    return ret;
}
