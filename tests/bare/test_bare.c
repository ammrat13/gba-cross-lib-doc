/**
    test_bare.c
    By: Ammar Ratnani

    Check that `game_bare.c` gives the right output to the screen. Should be
    mostly black save for three pixels that are red, green, and blue.

    For this file, the `state` is an `state_t**`
*/

// Include mGBA libraries
#include <mgba/core/core.h>
#include <mgba/core/log.h>
// Include our own libraries
#include "runner.h"


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

    // Create the core
    struct mCore *c = mCoreFind("bare/game_bare.thex");
    if(c == NULL) {
        fail_msg("Failed to allocate GBA core");
    }
    // Initialize it
    c->init(c);

    // Get video buffer dimensions
    unsigned int vW, vH;
    c->desiredVideoDimensions(c, &vW, &vH);
    // Allocate the video buffer
    color_t *vB = malloc(vH * vW * BYTES_PER_PIXEL);
    if(vB == NULL) {
        // Remember to destroy the core
        c->deinit(c);
        // Fail
        fail_msg("Failed to allocate video buffer");
    }
    // Initialize the video buffer
    c->setVideoBuffer(c, vB, vW);

    // Configure the core
    mCoreConfigInit(&c->config, NULL);
    mCoreConfigSetValue(&c->config, "idleOptimization", "ignore");

    // Actually load the file
    mCoreLoadFile(c, "bare/game_bare.thex");


    // Create the state structure
    // Free everything on failure
    state_t *s = malloc(sizeof(state_t));
    if(s == NULL) {
        // Destroy the core and its configuration
        mCoreConfigDeinit(&c->config);
        c->deinit(c);
        // Destroy the video buffer
        free(vB);
        // Fail
        fail_msg("Failed to allocate state");
    }
    // Initialize the state
    s->core = c;
    s->videoWidth = vW;
    s->videoHeight = vH;
    s->videoBuffer = vB;
    // Return
    *state = s;
    return 0;
}

// Delete the core
static int teardown_core(void **state) {

    // Get the state and core
    state_t *s = *state;
    struct mCore *c = s->core;

    // Free mGBA stuff
    mCoreConfigDeinit(&c->config);
    c->deinit(c);
    // Free the state
    free(s->videoBuffer);
    free(s);

    return 0;
}


// Check that the display is correct
static void test_display(void **state) {

    // Get the state and core
    state_t *s = *state;
    struct mCore *c = s->core;

    // Reset the core
    c->reset(c);
    // Step it for some time
    for(uint32_t i = 0; i < 1000; i++) {
        c->step(c);
    }

    // Check that the video buffer has the right contents
    for(unsigned int i = 0; i < s->videoHeight * s->videoWidth; i++) {
        assert_int_equal(s->videoBuffer[i], 0);
    }
}


// The suite to run
static const struct CMUnitTest suite[] = {
    cmocka_unit_test_setup_teardown(test_display, setup_core, teardown_core),
};
// Run the tests
int run_bare(void) {
    return cmocka_run_group_tests_name("bare", suite, NULL, NULL);
}
