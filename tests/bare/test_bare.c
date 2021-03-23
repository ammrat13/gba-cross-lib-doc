/**
    test_bare.c
    By: Ammar Ratnani

    Check that `game_bare.c` gives the right output to the screen. Should be
    mostly black save for three pixels that are red, green, and blue.

    For this file, the `state` is an `state_t**`
*/

#include "runner.h"

// Include mGBA libraries
#include <mgba/core/core.h>


// Define the state type
typedef struct state_t {
    // The GBA core
    struct mCore* core;
    // The video buffer and specifications
    unsigned int videoWidth;
    unsigned int videoHeight;
    color_t *videoBuffer;
} state_t;


// Setup the core
static int setup_core(void **state) {

    // Create the state structure
    state_t *s = malloc(sizeof(state_t));
    if(s == NULL) {
        fail_msg("Failed to allocate state");
    }

    // Create the core
    s->core = mCoreFind("bare/game_bare.thex");
    if(s->core == NULL) {
        free(s);
        fail_msg("Failed to allocate GBA core");
    }
    // Initialize it
    s->core->init(s->core);

    // Get video buffer dimensions
    s->core->desiredVideoDimensions(s->core, &s->videoWidth, &s->videoHeight);
    // Allocate the video buffer
    s->videoBuffer = malloc(s->videoHeight * s->videoWidth * BYTES_PER_PIXEL);
    if(s->videoBuffer == NULL) {
        free(s->core);
        free(s);
        fail_msg("Failed to allocate video buffer");
    }
    // Initialize the video buffer
    s->core->setVideoBuffer(s->core, s->videoBuffer, s->videoWidth);

    // Configure the core
    mCoreConfigInit(&s->core->config, NULL);
    mCoreConfigSetValue(&s->core->config, "idleOptimization", "ignore");

    // Actually load the file
    mCoreLoadFile(s->core, "bare/game_bare.thex");

    // Return the data
    *state = s;
    return 0;
}

// Check that the display is correct
static void test_display(void **state) {

    // Get the state
    state_t *s = *state;

    // Reset the core
    s->core->reset(s->core);
    // Step it for some time
    for(int i = 0; i < 1000; i++) {
        s->core->step(s->core);
    }

    // Check that the video buffer has the right contents
    for(unsigned int i = 0; i < s->videoHeight * s->videoWidth; i++) {
        assert_int_equal(s->videoBuffer[i], 0);
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
