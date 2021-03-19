/**
    game_bare.c
    By: Ammar Ratnani

    This file just displays three pixels on the screen. The test is whether this
    compiles correctly.
*/

// Copied from TONC
// See: https://www.coranac.com/tonc/text/first.htm

int main(void) {

    // Use Bitmap Mode 3
    *(unsigned int*)0x04000000 = 0x0403;

    // Set pixels to red, green, and blue respectively
    ((unsigned short*)0x06000000)[120+80*240] = 0x001F;
    ((unsigned short*)0x06000000)[136+80*240] = 0x03E0;
    ((unsigned short*)0x06000000)[120+96*240] = 0x7C00;

    // Return
    // Don't do the while(1), since we'll loop in the emulator
    return 0;
}
