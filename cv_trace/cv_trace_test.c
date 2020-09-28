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
        char const * p_callstack_name =
            cv_callstack_query(i_callstack_index);
        i_callstack_index ++;
        if (p_callstack_name) {
            cv_print_char('[');
            cv_print_0(p_callstack_name, 80);
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
        if (p_trace_count->p_parent) {
            cv_print_0(p_trace_count->p_parent, 80);
            cv_print_char('.');
        }
        if (p_trace_count->p_name) {
            cv_print_0(p_trace_count->p_name, 80);
        }
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
    static cv_array const o_map_name =
        cv_array_initializer_(a_map_name,
            a_map_name + sizeof a_map_name);
    static cv_trace_map o_trace_map = { 0 };
    if (cv_trace_map_init(&o_trace_map, &o_map_name,
        1024ul * 1024ul)) {
        {
            static char const a_sect_name[] = {
                'e', 'c', 'h', 'o'
            };
            static cv_array const o_sect_name =
                cv_array_initializer_(a_sect_name,
                    a_sect_name + sizeof a_sect_name);
            static char a_sect_region[1024u] = {0};
            static cv_array const o_sect_region =
                cv_array_initializer_(a_sect_region,
                    a_sect_region + sizeof a_sect_region);
            static cv_trace_sect o_echo = {0};
            /* create a section */
            cv_trace_sect_init(&o_echo, &o_sect_name, &o_sect_region, 1);
            /* print a message */
            cv_trace_sect_begin(&o_echo);
            {
                static char const a_hello[] = {
                    'h', 'e', 'l', 'l', 'o'
                };
                static cv_array const o_hello =
                    cv_array_initializer_(a_hello, a_hello + sizeof a_hello);
                cv_trace_sect_print(&o_hello);
            }
            cv_trace_sect_end();
            cv_trace_sect_cleanup(&o_echo);
        }
        {
            static cv_trace_func f1 = {0};
            cv_trace_func_init(&f1, "f1");
            {
                cv_trace_func_enter(&f1);
                cv_trace_test_dump_stack();
                cv_trace_func_leave();
            }
            cv_trace_test_func_report();
            cv_trace_func_cleanup(&f1);
        }
        cv_trace_map_cleanup(&o_trace_map);
    }
}

/* end-of-file: cv_trace_test.c */
