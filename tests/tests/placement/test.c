/*
    placement/test.c
    By: Ammar Ratnani

    Test to ensure that the the functionality to place things in the right
    sections works. Will run `placement/game.c` and check that the memory looks
    right.

    For this file, the `state` is a `gba_test_core_t**`
*/

// Include libraries
#include "lib.h"

// Setup the core
static int setup_test_memory_placement(void **state) {
    *state = init_gba_test_core("tests/placement/game.thex");
    return *state == NULL;
}

// Destroy the core
static int teardown_test_memory_placement(void **state) {
    deinit_gba_test_core(*state);
    return 0;
}


// Check that the memory was placed correctly
static void test_memory_placement(void **state) {

    // Get the state and core
    gba_test_core_t *tc = *state;

    // Reset the core
    tc->core->reset(tc->core);

    // Constants
    const uint32_t ewram_base = 0x02000000;
    const uint32_t ewram_end  = 0x02040000;
    const uint32_t iwram_base = 0x03000000;
    const uint32_t iwram_end  = 0x03008000;

    // Fill EWRAM and IWRAM with some magic number
    // This way we test that it was actually zeroed out
    for(uint32_t p = ewram_base; p < ewram_end; p++) {
        tc->core->rawWrite8(tc->core, p, 0, 0xff);
    }
    for(uint32_t p = iwram_base; p < iwram_end; p++) {
        tc->core->rawWrite8(tc->core, p, 0, 0xee);
    }

    // Let the program run to completion
    // Shouldn't take very long
    tc->core->runFrame(tc->core);

    // Check that EWRAM has the right contents
    const size_t ewram_ex_len = 12;
    const uint8_t ewram_ex_start[] = {
        0x44, 0x33, 0x22, 0x11,
        0x44, 0x33, 0x22, 0x11,
        0x00, 0x00, 0x00, 0x00
    };
    for(size_t i = 0; i < ewram_ex_len; i++) {
        uint8_t expected = ewram_ex_start[i];
        uint8_t actual = tc->core->rawRead8(tc->core, ewram_base + i, 0);
        if(expected != actual) {
            fail_msg(
                "Expected character 0x%02x instead of 0x%02x\n"
                "At memory address %zu",
                expected, actual, ewram_base + i);
        }
    }

    // Same for IWRAM
    const size_t iwram_ex_len = 8;
    const uint8_t iwram_ex_start[] = {
        0x88, 0x77, 0x66, 0x55,
        0x00, 0x00, 0x00, 0x00
    };
    for(size_t i = 0; i < iwram_ex_len; i++) {
        uint8_t expected = iwram_ex_start[i];
        uint8_t actual = tc->core->rawRead8(tc->core, iwram_base + i, 0);
        if(expected != actual) {
            fail_msg(
                "Expected character 0x%02x instead of 0x%02x\n"
                "At memory address %zu",
                expected, actual, iwram_base + i);
        }
    }
}


// The suite to run
static const struct CMUnitTest suite[] = {
    cmocka_unit_test_setup_teardown(
        test_memory_placement,
        setup_test_memory_placement,
        teardown_test_memory_placement),
};
// Run the tests
int run_placement(void) {
    return cmocka_run_group_tests_name("placement", suite, NULL, NULL);
}
