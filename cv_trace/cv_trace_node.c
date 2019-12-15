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
#include <cv_debug.h>
#include <cv_algo/cv_array_it.h>
#include <cv_algo/cv_array_print.h>
#include <cv_number_desc.h>
#include <cv_thread/cv_mutex_impl.h>

static cv_trace_node g_trace_footer =
cv_trace_node_initializer_(cv_trace_level_0, "footer");

static cv_trace_node * g_trace_list = &g_trace_footer;

static cv_mutex g_trace_mutex = cv_mutex_initializer_;

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
    /* mutex to protect list */
    /* link node into global list */
    /* read current clock */
    /* print of type */
    unsigned char a_line[80u];
    cv_array_it o_array_it = cv_array_it_initializer_;
    cv_debug_assert_(p_trace_node, cv_debug_code_null_ptr);
    cv_mutex_impl_lock(&g_trace_mutex);
    cv_trace_node_register(p_trace_node);
    cv_array_it_init_range(&o_array_it, a_line, a_line+sizeof(a_line));
    /* Update stats */
    /* process enter */
    /* process leave */
    /* process signal */
    {
        cv_clock_mono o_value = cv_clock_mono_initializer_;
        if (cv_clock_mono_read(&o_value)) {
            cv_clock_msec o_value_msec = cv_clock_msec_initializer_;
            cv_clock_get_msec(&o_value.o_clock, &o_value_msec);
            cv_array_print_unsigned(&o_array_it,
                o_value_msec.i_seconds, cv_number_format_dec());
            cv_array_print_char(&o_array_it, '.');
            cv_array_print_unsigned(&o_array_it,
                o_value_msec.i_mseconds, cv_number_format_dec());
            cv_array_print_char(&o_array_it, ':');
        }
    }
    cv_array_print_unsigned(&o_array_it, i_type, cv_number_format_dec());
    cv_array_print_char(&o_array_it, ':');
    cv_array_print_0(&o_array_it,
        p_trace_node->pc_text, cv_signed_short_max_);
    if (cv_array_print_nl(&o_array_it)) {
        if ((o_array_it.o_array.o_min.pc_uchar >= a_line) &&
            (o_array_it.o_array.o_min.pc_uchar <= a_line+sizeof(a_line))) {
            long const i_line_len = (o_array_it.o_array.o_min.pc_uchar -
                a_line) & cv_signed_long_max_;
            int const i_stdout = cv_runtime_stdout_fileno();
            cv_runtime_write(i_stdout, a_line, i_line_len);
        }
    }
    cv_array_it_cleanup(&o_array_it);
    cv_mutex_impl_unlock(&g_trace_mutex);
}

/*
 *
 */

static void cv_trace_node_profile_report_cb(
    cv_trace_node * p_iterator) {
    unsigned char a_line[80u];
    cv_array_it o_array_it = cv_array_it_initializer_;
    cv_array_it_init_range(&o_array_it, a_line, a_line+sizeof(a_line));
    cv_array_print_0(&o_array_it, p_iterator->pc_text,
        cv_signed_short_max_);
    if (cv_array_print_nl(&o_array_it)) {
        if ((o_array_it.o_array.o_min.pc_uchar >= a_line) &&
            (o_array_it.o_array.o_min.pc_uchar <= a_line+sizeof(a_line))) {
            long const i_line_len = (o_array_it.o_array.o_min.pc_uchar -
                a_line) & cv_signed_long_max_;
            int const i_stdout = cv_runtime_stdout_fileno();
            cv_runtime_write(i_stdout, a_line, i_line_len);
        }
    }
    cv_array_it_cleanup(&o_array_it);
}

/*
 *
 */

void cv_trace_node_profile_report(void) {
    cv_trace_node * p_iterator = g_trace_list;
    while (p_iterator && (p_iterator != &g_trace_footer)) {
        cv_trace_node_profile_report_cb(p_iterator);
        p_iterator = p_iterator->p_next;
    }
}

/* end-of-file: cv_trace_node.c */
