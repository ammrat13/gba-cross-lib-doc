/*
    silent_log.h
    By: Ammar Ratnani

    This file provides declarations for silent logging functionality. By
    default, mGBA logs to STDOUT. This is undesireable since we use STDOUT for
    test output. Thus, this file.

    It includes the logging functionality of mGBA.
*/

#ifndef SILENT_LOG_H
#define SILENT_LOG_H

#ifdef __cplusplus
extern "C" {
#endif


// Include libraries
#include <mgba/core/log.h>


// Silent logger to pass to mGBA
extern struct mLogger silent_logger;


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ndef SILENT_LOG_H
