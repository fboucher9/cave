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
#include <pthread.h>

static cv_trace_node g_trace_footer =
cv_trace_node_initializer_(cv_trace_level_0, "footer");

static cv_trace_node * g_trace_list = &g_trace_footer;

static pthread_mutex_t g_trace_mutex = PTHREAD_MUTEX_INITIALIZER;

static unsigned char const a_period[] = { '.' };

static unsigned char const a_colon[] = { ':' };

static unsigned char const a_newline[] = { '\n' };

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
    int const i_stdout = cv_runtime_stdout_fileno();
    cv_debug_assert_(!!p_trace_node, cv_debug_code_null_ptr);
    pthread_mutex_lock(&g_trace_mutex);
    cv_trace_node_register(p_trace_node);
    /* Update stats */
    /* process enter */
    /* process leave */
    /* process signal */
    {
        cv_clock_mono o_value = cv_clock_mono_initializer_;
        if (cv_clock_mono_read(&o_value)) {
            cv_clock_msec o_value_msec = cv_clock_msec_initializer_;
            cv_clock_get_msec(&o_value.o_clock, &o_value_msec);
            cv_runtime_print_ld(i_stdout,
                cv_cast_(long, o_value_msec.i_seconds));
            cv_runtime_write(i_stdout, a_period, cv_sizeof_(a_period));
            cv_runtime_print_ld(i_stdout,
                cv_cast_(long, o_value_msec.i_mseconds));
            cv_runtime_write(i_stdout, a_colon, cv_sizeof_(a_colon));
        }
    }
    cv_runtime_print_ld(i_stdout, i_type);
    cv_runtime_write(i_stdout, a_colon, cv_sizeof_(a_colon));
    {
        long const i_text_len = cv_memory_find_0(p_trace_node->pc_text,
            cv_signed_short_max_);
        cv_runtime_write(i_stdout, p_trace_node->pc_text, i_text_len);
    }
    cv_runtime_write(i_stdout, a_newline, cv_sizeof_(a_newline));
    pthread_mutex_unlock(&g_trace_mutex);
}

/*
 *
 */

void cv_trace_node_profile_report(void) {
    int const i_stdout = cv_runtime_stdout_fileno();
    cv_trace_node * p_iterator = g_trace_list;
    while (p_iterator && (p_iterator != &g_trace_footer)) {
        {
            long const i_text_len = cv_memory_find_0(p_iterator->pc_text,
                cv_signed_short_max_);
            cv_runtime_write(i_stdout, p_iterator->pc_text, i_text_len);
        }
        cv_runtime_write(i_stdout, a_newline, cv_sizeof_(a_newline));
        p_iterator = p_iterator->p_next;
    }
}

/* end-of-file: cv_trace_node.c */
