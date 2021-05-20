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
int IWRAM_DATA(c) = 0x55667788;
int IWRAM_BSS(d);

// EWRAM
int EWRAM_DATA(e) = 0x11223344;
int EWRAM_BSS(f);


// Main not required
int main(void){
    return 0;
}
