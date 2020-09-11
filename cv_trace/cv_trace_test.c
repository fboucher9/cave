/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_test.h>
#include <cv_trace/cv_trace.h>
#include <cv_algo/cv_array.h>
#include <cv_test_print.h>

/*
 *
 */

void cv_trace_test(void) {
    static char const a_map_name[] = {
        'c', 'a', 'v', 'e', '_', 't', 'e', 's', 't'
    };
    static cv_array const o_map_name = cv_array_initializer_(a_map_name,
        a_map_name + sizeof a_map_name);
    static cv_trace_map o_trace_map = { 0 };
    if (cv_trace_map_init(&o_trace_map, &o_map_name,
        1024ul * 1024ul)) {
        static char const a_f1_name[] = { 'f', '1' };
        static cv_array const o_f1_name = cv_array_initializer_(a_f1_name,
            a_f1_name + sizeof a_f1_name);
#if 0
        cv_trace_sect * const p_trace_info = cv_trace_level_get(p_trace_map,
            cv_trace_level_info);
#endif
        static cv_trace_func f1 = {0};
        cv_trace_func_init(&f1, &o_f1_name);
        {
            cv_trace_func_enter(&f1);
            cv_print_0("--- stack ---", 80);
            cv_print_nl();
            /* cv_trace_stack_report(); */
            cv_print_0("--- end ---", 80);
            cv_print_nl();
            cv_trace_func_leave();
        }
        cv_trace_func_cleanup(&f1);
        cv_trace_map_cleanup(&o_trace_map);
    }
    cv_print_0("--- profile ---", 80);
    cv_print_nl();
    /* cv_trace_profile_summary_report(); */
    cv_print_0("--- end ---", 80);
    cv_print_nl();
}

/* end-of-file: cv_trace_test.c */
