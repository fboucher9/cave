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
#include <cv_clock/cv_clock_tick.h>
#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_algo/cv_array_it.h>
#include <cv_algo/cv_array_print.h>
#include <cv_number/cv_number_format.h>
#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

/*
 *
 */

#if defined cv_have_libc_
static void cv_trace_test_markup_1(void) {
    static char a_storage[1024];
    cv_clock_tick o_tick_enter;
    cv_clock_tick o_tick_leave;
    cv_clock_tick_read(&o_tick_enter);
    {
        unsigned long i_repeat = 1000;
        while (i_repeat --) {
            sprintf(a_storage, "%lu", i_repeat);
        }
    }
    cv_clock_tick_read(&o_tick_leave);
    {
        cv_ull i_elapsed = 0;
        {
            cv_ull i_enter_clock = cv_clock_get(&o_tick_enter.o_clock);
            cv_ull i_leave_clock = cv_clock_get(&o_tick_leave.o_clock);
            i_elapsed = i_leave_clock - i_enter_clock;
        }
        cv_print_0("trace_markup_1 elapsed=", 80);
        cv_print_dec(i_elapsed & cv_signed_long_max_);
        cv_print_nl();
    }
}
#endif /* #if defined cv_have_libc_ */

/*
 *
 */

static void cv_trace_test_markup_2(void) {
    static unsigned char a_storage[1024u];
    cv_clock_tick o_tick_enter;
    cv_clock_tick o_tick_leave;
    cv_array o_storage;
    cv_clock_tick_read(&o_tick_enter);
    cv_array_init_vector(&o_storage, a_storage, sizeof(a_storage));
    {
        unsigned long i_repeat = 1000;
        while (i_repeat --) {
            cv_array_it o_array_it;
            cv_array_it_init(&o_array_it, &o_storage);
            cv_array_print_signed(&o_array_it,
                i_repeat & cv_signed_long_max_,
                cv_number_format_dec());
            cv_array_it_cleanup(&o_array_it);
        }
    }
    cv_array_cleanup(&o_storage);
    cv_clock_tick_read(&o_tick_leave);
    {
        cv_ull i_elapsed = 0;
        {
            cv_ull i_enter_clock = cv_clock_get(&o_tick_enter.o_clock);
            cv_ull i_leave_clock = cv_clock_get(&o_tick_leave.o_clock);
            i_elapsed = i_leave_clock - i_enter_clock;
        }
        cv_print_0("trace_markup_2 elapsed=", 80);
        cv_print_dec(i_elapsed & cv_signed_long_max_);
        cv_print_nl();
    }
}

/*
 *  cv_trace_test_markup()
 *
 *  Verify performance of markup techniques.  First verify traditionnal
 *  printf, then verify number formatting code.  Then verify the unicode
 *  markup.
 */

static void cv_trace_test_markup(void) {
#if defined cv_have_libc_
    cv_trace_test_markup_1();
#endif /* #if defined cv_have_libc_ */
    cv_trace_test_markup_2();
#if 0
    cv_trace_test_markup_3();
#endif
}

/*
 *
 */

static void cv_trace_test_dump_stack(void) {
    cv_print_0("--- stack ---", 80);
    cv_print_nl();
    /* cv_trace_stack_report(); */
#if defined cv_have_callstack_
    {
        unsigned char i_callstack_count = cv_callstack_count();
        unsigned char i_callstack_index = 0;
        while (i_callstack_index < i_callstack_count) {
            union cv_callstack_value o_stack_value;
            unsigned char e_stack_type =
                cv_callstack_query(i_callstack_index, &o_stack_value);
            i_callstack_index ++;
            if (cv_callstack_type_function == e_stack_type) {
                cv_print_char('[');
                cv_print_0(o_stack_value.p_text, 80);
                cv_print_char(']');
                cv_print_nl();
            }
        }
    }
#endif /* #if defined cv_have_callstack_ */
    cv_print_0("--- end ---", 80);
    cv_print_nl();
}

/*
 *
 */

static void cv_trace_test_func_report(void) {
    cv_trace_count_it o_it;
    cv_trace_count_ptr o_ptr;
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
    cv_trace_test_markup();
    {
        static char const a_map_name[] = {
            'c', 'a', 'v', 'e', '_', 't', 'e', 's', 't'
        };
        static cv_array const o_map_name =
            cv_array_initializer_(a_map_name,
                a_map_name + sizeof a_map_name);
        static cv_trace_map o_trace_map;
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
                static cv_trace_sect o_echo;
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
                static cv_trace_func f1;
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
}

/* end-of-file: cv_trace_test.c */
