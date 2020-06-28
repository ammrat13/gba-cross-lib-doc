/*
    crtin_common.c
    By: Ammar Ratnani

    Implementation file for the corresponding header. Defines functions common
    to `crti` and `crtn`, most prominently the function to call a table of
    function pointers given its start and length.
*/

#include "crtin_common.h"

#ifdef __cplusplus
extern "C" {
#endif


__attribute__((target("thumb")))
void _call_func_table(void (*tab[])(void), size_t len) {
    // Iterate through, calling all the functions
    for(size_t i = 0; i < len; i++)
        (*tab[i])();
}


#ifdef __cplusplus
} // extern "C"
#endif

