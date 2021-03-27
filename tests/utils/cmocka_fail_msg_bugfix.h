/*
    cmocka_fail_msg_bugfix.h
    By: Ammar Ratnani

    By default, `fail_msg` will print errors to STDOUT. This is undesireable.
    Instead, it should print the error in the JUnit XML. This header patches the
    issue.

    It also changes the formatting of `fail_msg` slightly.
*/

// Our issue is with cmocka, so import it and its dependencies
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


// Use this printing function instead
void cm_print_error(const char *format, ...) CMOCKA_PRINTF_ATTRIBUTE(1, 2);

// Redefine fail_msg
#undef fail_msg
#define fail_msg(msg, ...) do { \
    cm_print_error(msg "\n", ##__VA_ARGS__); \
    fail(); \
} while(0)
