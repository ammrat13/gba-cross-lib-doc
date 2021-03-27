/**
    test_bare.c
    By: Ammar Ratnani

    Check that `game_bare.c` gives the right output to the screen. Should be
    mostly black save for three pixels that are red, green, and blue.

    For this file, the `state` is an `state_t**`
*/

// Include mGBA libraries
#include <mgba/core/core.h>
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
    struct mCore *c = mCoreFind("tests/bare_game.thex");
    if(c == NULL) {
        fail_msg("Failed to allocate GBA core");
    }
    // Initialize it
    c->init(c);

    // Get video buffer dimensions
    unsigned int vW, vH;
    c->desiredVideoDimensions(c, &vW, &vH);
    // Check we got the right dimensions
    if(vW != 240 || vH != 160) {
        // Remember to destroy the core
        c->deinit(c);
        // Fail
        fail_msg("Incorrect video dimensions");
    }

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
    mCoreLoadFile(c, "tests/bare_game.thex");


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
    // Run for a few frames to let the initialization complete
    // Three frames seems to be the minimum
    for(uint32_t i = 0; i < 3; i++) {
        c->runFrame(c);
    }

    // Check that the video buffer has the right contents
    for(unsigned int i = 0; i < s->videoHeight * s->videoWidth; i++) {
        // Check for special values
        switch(i) {
            case 120+80*240:
                assert_int_equal(s->videoBuffer[i] & 0xffffff, 0x0000ff);
                break;
            case 136+80*240:
                assert_int_equal(s->videoBuffer[i] & 0xffffff, 0x00ff00);
                break;
            case 120+96*240:
                assert_int_equal(s->videoBuffer[i] & 0xffffff, 0xff0000);
                break;
            default:
                assert_int_equal(s->videoBuffer[i] & 0xffffff, 0);
                break;
        }
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
