/* See LICENSE for license details */

#ifndef cv_trace_h_
#define cv_trace_h_

/*
 *  Module: cv_trace.h
 *
 *  Description: Generic trace system for libraries and applications.  An
 *      instance must be initialized for each library and application.
 *
 *  Comments:
 *
 *      - Map object represents memory mapping of a log file.  Each instance
 *      manages list of functions, events and sections.
 *
 *      - Functions and events are associated with a map object in order to
 *      produce the period and summary reports.
 *
 *      - Each map object has some base sections for common events like
 *      process, thread, period and summary.
 *
 *      - Custom sections may be added to common sections.
 *
 *      - Use of TLS to avoid locking from time critical functions.  Update of
 *      global variables is done when cache is full or when flush is possible.
 *
 *      - Cache of rdtsc in TLS to avoid reading clock too many times.
 */

#include <cv_trace/cv_trace_plugin.h>
#include <cv_trace/cv_trace_map.h>
#include <cv_trace/cv_trace_level.h>
#include <cv_trace/cv_trace_sect.h>
#include <cv_trace/cv_trace_count.h>
#include <cv_trace/cv_trace_func.h>

#endif /* #ifndef cv_trace_h_ */

/* end-of-file: cv_trace.h */
