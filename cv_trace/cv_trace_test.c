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
#include <cv_test_print.h>

/*
 *
 */

void cv_trace_test(void) {
    cv_clock_duration o_duration = cv_clock_duration_initializer_;
    cv_clock_duration_init_msec(&o_duration, 0, 100);
    {
        cv_trace_func0_decl_(f1, "f1");
        cv_trace_func0_enter_(f1);
        cv_clock_duration_until(&o_duration);
        {
            cv_trace_func0_decl_(f2, "f2");
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
            cv_print_0("--- stack ---", 80);
            cv_print_nl();
            cv_trace_node_stack_report();
            cv_print_0("--- end ---", 80);
            cv_print_nl();
            {
                char const * a_stack[4u];
                long i_count = cv_trace_node_stack_query(
                    a_stack,
                    4u);
                if ((i_count > 0) && (i_count <= 4)) {
                    long i_index = 0;
                    while (i_index < i_count) {
                        cv_print_char('[');
                        cv_print_0(a_stack[i_index], 80);
                        cv_print_char(']');
                        cv_print_nl();
                        i_index ++;
                    }
                }
            }
            cv_clock_duration_until(&o_duration);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
            {
                char const * a_stack[4u];
                long i_count = cv_trace_node_stack_query(
                    a_stack,
                    4u);
                if ((i_count > 0) && (i_count <= 4)) {
                    long i_index = 0;
                    while (i_index < i_count) {
                        cv_print_char('[');
                        cv_print_0(a_stack[i_index], 80);
                        cv_print_char(']');
                        cv_print_nl();
                        i_index ++;
                    }
                }
            }
            cv_trace_func0_leave_(f2);
            cv_trace_func0_leave_(f2);
        }
        cv_clock_duration_until(&o_duration);
        cv_trace_func0_leave_(f1);
    }
    cv_clock_duration_cleanup(&o_duration);
    cv_print_0("--- profile ---", 80);
    cv_print_nl();
    cv_trace_node_profile_report();
    cv_print_0("--- end ---", 80);
    cv_print_nl();
}

/* end-of-file: cv_trace_test.c */
