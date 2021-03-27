/*
    gba_test_core.h
    By: Ammar Ratnani

    This file provides utility functions for working with GBA cores in tests. In
    particular, it gives functions to setup and teardown the cores, and provides
    a method of passing data between these functions and tests.
*/

#ifndef GBA_CORE_H
#define GBA_CORE_H

#ifdef __cplusplus
extern "C" {
#endif


// Requires mGBA
#include <mgba/core/core.h>
// Utility libraries
#include <stdint.h>


// Constants for the GBA
#define GBA_DISP_ROWS (160)
#define GBA_DISP_COLS (240)


// Structure for GBA cores in tests
typedef struct gba_test_core_t {
    // The actual core
    struct mCore *core;
    // The video
    // Indexed as a 2D array in row-major order
    color_t (*video_buffer)[GBA_DISP_COLS];
} gba_test_core_t;


// Functions to initialize and deinitialize GBA cores for testing
// Initialization returns NULL on failure
gba_test_core_t *init_gba_test_core(const char *fname);
void deinit_gba_test_core(gba_test_core_t *to_destroy);

// Utility functions
uint32_t mgba_color_to_rgb(color_t in);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef GBA_CORE_H
