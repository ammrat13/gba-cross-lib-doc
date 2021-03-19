/**
    test_bare.c
    By: Ammar Ratnani

    Currently, it will always pass.
*/

#include "runner.h"

START_TEST(write_name) {
    printf("# bare\n");
} END_TEST

START_TEST(do_test) {
    ck_assert_int_eq(0,0);
} END_TEST

Suite *suite_bare(void) {
    Suite *ret = suite_create("bare");
    TCase *cas = tcase_create("do_test");
    tcase_add_test(cas, write_name);
    tcase_add_test(cas, do_test);
    suite_add_tcase(ret, cas);
    return ret;
}
