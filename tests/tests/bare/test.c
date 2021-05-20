/**
    bare/test.c
    By: Ammar Ratnani

    Check that `bare/game.c` gives the right output to the screen. Should be
    mostly black save for three pixels that are red, green, and blue.

    For this file, the `state` is a `gba_test_core_t**`
*/

// Include libraries
#include "lib.h"


// Setup the core
static int setup_test_display(void **state) {
    *state = init_gba_test_core("tests/bare/game.thex");
    return *state == NULL;
}

// Destroy the core
static int teardown_test_display(void **state) {
    deinit_gba_test_core(*state);
    return 0;
}


// Check that the display is correct
static void test_display(void **state) {

    // Get the state and core
    gba_test_core_t *tc = *state;

    // Reset the core
    tc->core->reset(tc->core);
    // Run for a few frames to let the initialization complete
    // Three frames seems to be the minimum
    for(uint32_t i = 0; i < 3; i++) {
        tc->core->runFrame(tc->core);
    }

    // Check that the video buffer has the right contents
    for(size_t r = 0; r < GBA_DISP_ROWS; r++) {
        for(size_t c = 0; c < GBA_DISP_COLS; c++) {

            // Compute the expected value
            uint32_t expected =
                (r == 80 && c == 120) ? 0xff0000 :
                (r == 80 && c == 136) ? 0x00ff00 :
                (r == 96 && c == 120) ? 0x0000ff :
                0x000000;
            // Get the actual
            uint32_t actual = mgba_color_to_rgb(tc->video_buffer[r][c]);

            // Check for equality
            if(expected != actual) {
                fail_msg(
                    "Expected color 0x%06x instead of 0x%06x\n"
                    "At row %zu column %zu",
                    expected, actual, r, c);
            }
        }
    }
}


// The suite to run
const struct CMUnitTest cmtest_bare =
    cmocka_unit_test_setup_teardown(
        test_display,
        setup_test_display,
        teardown_test_display
    );
