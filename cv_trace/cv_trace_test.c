/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_test.h>
#include <cv_trace/cv_trace_func.h>
#include <cv_trace/cv_trace_func0.h>
#include <cv_trace/cv_trace_event.h>
#include <cv_trace/cv_trace_node.h>
#include <cv_clock/cv_clock_duration.h>
#include <cv_clock/cv_clock_tool.h>

/*
 *
 */

void cv_trace_test(void) {
    cv_clock_msec o_clock_msec = cv_clock_msec_initializer_;
    cv_clock_duration o_duration = cv_clock_duration_initializer_;
    cv_clock_duration_init(&o_duration);
    o_clock_msec.i_seconds = 0;
    o_clock_msec.i_mseconds = 100;
    cv_clock_set_msec(&o_duration.o_clock, &o_clock_msec);
    {
        cv_trace_func0_decl_(f1);
        cv_trace_func0_enter_(f1);
        cv_clock_duration_until(&o_duration);
        {
            cv_trace_func0_decl_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_trace_func0_enter_(f2);
            cv_clock_duration_until(&o_duration);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
        }
        cv_clock_duration_until(&o_duration);
        cv_trace_func0_leave_(f1);
    }
    cv_clock_duration_cleanup(&o_duration);
    cv_trace_node_profile_report();
}

/* end-of-file: cv_trace_test.c */
