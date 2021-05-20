/*
    placement/game.c
    By: Ammar Ratnani

    Ensure that we can place things in the right sections. We will simply
    declare variables then assert they were placed in the right place.
*/


// IWRAM Implicit
int a = 0x55667788;
int b;

// IWRAM Explicit
__attribute__((section(".iwram_data.c"))) int c = 0x55667788;
__attribute__((section(".iwram_bss.d")))  int d;

// EWRAM
__attribute__((section(".ewram_data.e"))) int e = 0x11223344;
__attribute__((section(".ewram_bss.f")))  int f;


// Main not required
int main(void){
    return 0;
}
