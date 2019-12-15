/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_test.h>
#include <cv_trace/cv_trace_func.h>
#include <cv_trace/cv_trace_func0.h>
#include <cv_trace/cv_trace_event.h>
#include <cv_trace/cv_trace_node.h>

/*
 *
 */

void cv_trace_test(void) {
    cv_trace_func0_decl_(f1);
    cv_trace_func0_enter_(f1);
    cv_trace_func0_leave_(f1);
    cv_trace_node_profile_report();
}

/* end-of-file: cv_trace_test.c */
