/**
    test_bare.c
    By: Ammar Ratnani

    Currently, it will always pass.
*/

#include "runner.h"

START_TEST(do_test) {
    ck_assert_int_eq(1,0);
} END_TEST

Suite *suite_bare(void) {
    Suite *ret = suite_create("Bare");
    TCase *cas = tcase_create("do_test");
    tcase_add_test(cas, do_test);
    suite_add_tcase(ret, cas);
    return ret;
}
