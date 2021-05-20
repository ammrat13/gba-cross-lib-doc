/*
    placement/game.c
    By: Ammar Ratnani

    Ensure that we can place things in the right sections. We will simply
    declare variables then assert they were placed in the right place.
*/

// Test our library for this
#include <placement.h>


// IWRAM Implicit
int a = 0x55667788;
int b;

// IWRAM Explicit
int IDATA(c) = 0x55667788;
int IBSS(d);

// EWRAM
int EDATA(e) = 0x11223344;
int EBSS(f);


// Main not required
int main(void){
    return 0;
}
