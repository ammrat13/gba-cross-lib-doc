/**
    test_bare.c
    By: Ammar Ratnani

    Check that `game_bare.c` gives the right output to the screen. Should be
    mostly black save for three pixels that are red, green, and blue.

    For this file, the `state` is an `struct mCore**`
*/

#include "runner.h"

// Include mGBA libraries
#include <mgba/core/core.h>


// Setup the core
static int setup_core(void **state) {

    // Create the core
    struct mCore *core = mCoreFind("bare/game_bare.to");
    assert_non_null(core);
    // Initialize
    core->init(core);

    // Configure the core
    mCoreConfigInit(&core->config, NULL);
    mCoreConfigSetValue(&core->config, "idleOptimization", "ignore");

    // Actually load the file
    mCoreLoadFile(core, "bare/game_bare.to");

    // Return
    *state = core;
    return 0;
}

// Check that the display is correct
static void test_display(void **state) {

    // Get the core
    struct mCore *core = *state;

    // Get video buffer dimensions
    unsigned int videoHeight, videoWidth;
    core->desiredVideoDimensions(core, &videoWidth, &videoHeight);
    // Initialize the video buffer
    color_t videoBuffer[videoHeight][videoWidth];
    core->setVideoBuffer(core, (color_t*) videoBuffer, videoWidth);

    // Step it for some time
    for(int i = 0; i < 1000; i++) {
        core->step(core);
    }

    // Check that the video buffer has the right contents
    for(unsigned int r = 0; r < videoHeight; r++) {
        for(unsigned int c = 0; c < videoWidth; c++) {
            assert_int_equal(videoBuffer[r][c], 0);
        }
    }
}


// The suite to run
static const struct CMUnitTest suite[] = {
    cmocka_unit_test_setup(test_display, setup_core),
};
// Run the tests
int run_bare(void) {
    return cmocka_run_group_tests_name("bare", suite, NULL, NULL);
}
