/*
    gba_test_core.c
    By: Ammar Ratnani

    Implementation file for `gba_core.h`. It defines the constants and provides
    implementations for the initialization / deinitialization methods.
*/

#include "gba_test_core.h"


// Initialization
// Just malloc everything we need
gba_test_core_t *init_gba_test_core(const char *fname) {

    // Allocate space for the return value
    // Need to `calloc` so all pointers are `NULL`
    gba_test_core_t *ret = calloc(1, sizeof(gba_test_core_t));
    if(ret == NULL) {
        deinit_gba_test_core(ret);
        return NULL;
    }

    // Try to make the core
    ret->core = mCoreFind(fname);
    // Check for NULL and assert we have the right platform
    if(ret->core == NULL) {
        deinit_gba_test_core(ret);
        return NULL;
    }
    // Don't forget the initialization step
    ret->core->init(ret->core);

    // Configure the core
    // Need to do this now since mGBA doesn't set the config to NULL
    mCoreConfigInit(&ret->core->config, NULL);
    mCoreConfigSetValue(&ret->core->config, "idleOptimization", "ignore");
    // Load the file
    mCoreLoadFile(ret->core, fname);


    // Assert that the platform is correct
    enum mPlatform pl = ret->core->platform(ret->core);
    if(pl != PLATFORM_GBA) {
        deinit_gba_test_core(ret);
        return NULL;
    }
    // Assert that desired video dimensions are correct
    unsigned int vR, vC;
    ret->core->desiredVideoDimensions(ret->core, &vC, &vR);
    if(vR != GBA_DISP_ROWS || vC != GBA_DISP_COLS) {
        deinit_gba_test_core(ret);
        return NULL;
    }

    // Allocate the video buffer
    ret->video_buffer = calloc(GBA_DISP_ROWS * GBA_DISP_COLS, BYTES_PER_PIXEL);
    if(ret->video_buffer == NULL) {
        deinit_gba_test_core(ret);
        return NULL;
    }
    // Set the core to use the buffer
    ret->core->setVideoBuffer(
        ret->core,
        (color_t*) ret->video_buffer,
        GBA_DISP_COLS);

    // Return
    return ret;
}


// Deinitialization
// Just free everything
void deinit_gba_test_core(gba_test_core_t *to_destroy) {

    // Check for nulls
    if(to_destroy == NULL) {
        return;
    }

    // Free the video buffer if it exists
    // Take advantage of `free` NOPing when passed NULL
    free(to_destroy->video_buffer);

    // Free the core if it exists
    // We don't have any tricks here
    if(to_destroy->core != NULL) {
        // Check the configuration first
        mCoreConfigDeinit(&to_destroy->core->config);
        // Free the core itself
        to_destroy->core->deinit(to_destroy->core);
    }

    // Free the containing structure
    free(to_destroy);
}


// Utility function to convert colors from mGBA to RGB format
// mGBA stores in AGBR
// Drop the Alpha and reorder
uint32_t mgba_color_to_rgb(color_t in) {
    // Components
    uint8_t r = (in >>  0) & 0xff;
    uint8_t g = (in >>  8) & 0xff;
    uint8_t b = (in >> 16) & 0xff;
    // Reorder
    return (r << 16) | (g << 8) | (b << 0);
}
