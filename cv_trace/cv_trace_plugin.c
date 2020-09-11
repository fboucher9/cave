/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_plugin.h>
#include <cv_trace/cv_trace.h>

/*
 *
 */

cv_bool cv_trace_load(void) {
    cv_trace_func_load();
    return cv_true;
}

/*
 *
 */

void cv_trace_unload(void) {
    cv_trace_func_unload();
}

/* end-of-file: cv_trace_plugin.c */
