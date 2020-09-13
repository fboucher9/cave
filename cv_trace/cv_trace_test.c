/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_test.h>
#include <cv_trace/cv_trace.h>
#include <cv_algo/cv_array.h>
#include <cv_test_print.h>
#include <cv_algo/cv_callstack.h>
#include <cv_misc/cv_limits.h>

/*
 *
 */

static void cv_trace_test_dump_stack(void) {
    unsigned char i_callstack_count = cv_callstack_count();
    unsigned char i_callstack_index = 0;
    cv_print_0("--- stack ---", 80);
    cv_print_nl();
    /* cv_trace_stack_report(); */
    while (i_callstack_index < i_callstack_count) {
        cv_array const * p_callstack_name =
            cv_callstack_query(i_callstack_index);
        i_callstack_index ++;
        if (p_callstack_name) {
            cv_print_char('[');
            cv_print_array(p_callstack_name);
            cv_print_char(']');
            cv_print_nl();
        }
    }
    cv_print_0("--- end ---", 80);
    cv_print_nl();
}

/*
 *
 */

static void cv_trace_test_func_report(void) {
    cv_trace_count_it o_it = {0};
    cv_trace_count_ptr o_ptr = {0};
    cv_print_0("--- profile ---", 80);
    cv_print_nl();
    /* cv_trace_profile_summary_report(); */
    cv_trace_count_it_init(&o_it);
    while (cv_trace_count_it_next(&o_it, &o_ptr)) {
        cv_trace_count const * p_trace_count = o_ptr.pc_trace_count;
        cv_print_char('[');
        cv_print_array(&p_trace_count->o_parent);
        cv_print_char('.');
        cv_print_array(&p_trace_count->o_name);
        cv_print_char(']');
        cv_print_char(':');
        {
            long const i_number =
                p_trace_count->i_period_count & cv_signed_long_max_;
            cv_print_dec(i_number);
        }
        cv_print_char(',');
        {
            long const i_number =
                p_trace_count->i_summary_count & cv_signed_long_max_;
            cv_print_dec(i_number);
        }
        cv_print_nl();
    }
    cv_trace_count_it_cleanup(&o_it);
    cv_print_0("--- end ---", 80);
    cv_print_nl();
}

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
        /* create a section */
        /* print a message */
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
            cv_trace_test_dump_stack();
            cv_trace_func_leave();
        }
        cv_trace_test_func_report();
        cv_trace_func_cleanup(&f1);
        cv_trace_map_cleanup(&o_trace_map);
    }
}

/* end-of-file: cv_trace_test.c */
