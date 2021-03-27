/*
    silent_log.c
    By: Ammar Ratnani

    Implementation file for silent logging.
*/

#include "silent_log.h"


// Define the logger
struct mLogger silent_logger = {
    .log = silent_log,
    .filter = NULL,
};

// Define the log function
void silent_log(
    struct mLogger* logger,
    int category,
    enum mLogLevel level,
    const char *format,
    va_list args
) {
    /* Do nothing */
}
