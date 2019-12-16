/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_node.h>
#include <cv_misc/cv_unused.h>
#include <cv_runtime.h>
#include <cv_memory.h>
#include <cv_misc/cv_limits.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_clock/cv_clock_mono.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_debug/cv_debug.h>
#include <cv_number_desc.h>
#include <cv_thread/cv_mutex.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file_print.h>

static cv_trace_node g_trace_footer =
cv_trace_node_initializer_(cv_trace_level_0, "footer");

static cv_trace_node * g_trace_list = &g_trace_footer;

static cv_mutex g_trace_mutex = cv_mutex_initializer_;

static cv_thread_local_ long i_recursive = 0;

/*
 *
 */

static void cv_trace_node_register( cv_trace_node * p_trace_node ) {
    if (p_trace_node->p_next) {
    } else {
        p_trace_node->p_next = g_trace_list;
        g_trace_list = p_trace_node;
    }
}

/*
 *
 */

void cv_trace_node_dispatch( cv_trace_node * p_trace_node,
    unsigned char i_type) {
    if (0 == (i_recursive++)) {
        /* mutex to protect list */
        /* link node into global list */
        /* read current clock */
        /* print of type */
        cv_file const * p_stdout = cv_file_std_out();
        cv_debug_assert_(p_trace_node, cv_debug_code_null_ptr);
        cv_mutex_impl_lock(&g_trace_mutex);
        cv_trace_node_register(p_trace_node);
        cv_mutex_impl_unlock(&g_trace_mutex);
        /* Update stats */
        /* process enter */
        /* process leave */
        /* process signal */
        {
            cv_clock_mono o_value = cv_clock_mono_initializer_;
            if (cv_clock_mono_read(&o_value)) {
                cv_clock_msec o_value_msec = cv_clock_msec_initializer_;
                cv_clock_get_msec(&o_value.o_clock, &o_value_msec);
                cv_file_print_unsigned(p_stdout,
                    o_value_msec.i_seconds, cv_number_format_dec());
                cv_file_print_char(p_stdout, '.');
                cv_file_print_unsigned(p_stdout,
                    o_value_msec.i_mseconds, cv_number_format_dec());
                cv_file_print_char(p_stdout, ':');
            }
        }
        cv_file_print_unsigned(p_stdout, i_type, cv_number_format_dec());
        cv_file_print_char(p_stdout, ':');
        cv_file_print_0(p_stdout,
            p_trace_node->pc_text, cv_signed_short_max_);
        cv_file_print_nl(p_stdout);
    }
    i_recursive --;
}

/*
 *
 */

static void cv_trace_node_profile_report_cb(
    cv_trace_node * p_iterator) {
    cv_file const * p_stdout = cv_file_std_out();
    cv_file_print_0(p_stdout, p_iterator->pc_text,
        cv_signed_short_max_);
    cv_file_print_nl(p_stdout);
}

/*
 *
 */

void cv_trace_node_profile_report(void) {
    if (0 == (i_recursive++)) {
        cv_trace_node * p_iterator = g_trace_list;
        while (p_iterator && (p_iterator != &g_trace_footer)) {
            cv_trace_node_profile_report_cb(p_iterator);
            p_iterator = p_iterator->p_next;
        }
    }
    i_recursive --;
}

/* end-of-file: cv_trace_node.c */
