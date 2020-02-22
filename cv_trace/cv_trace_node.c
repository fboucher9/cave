/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_node.h>
#include <cv_runtime.h>
#include <cv_memory.h>
#include <cv_misc/cv_limits.h>
#include <cv_clock/cv_clock_mono.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_debug/cv_debug.h>
#include <cv_number/cv_number_desc.h>
#include <cv_thread/cv_mutex_impl.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_trace/cv_trace_msg.h>
#include <cv_clock/cv_clock_duration.h>
#include <cv_thread/cv_specific.h>
#include <cv_trace/cv_trace_level.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

extern struct cv_specific cv_trace_key;

static cv_trace_global g_trace_footer_global =
cv_trace_global_initializer_(cv_trace_type_func_enter,
    cv_trace_level_0, "dummy");

static cv_trace g_trace_footer_local =
cv_trace_initializer_(g_trace_footer_global);

static cv_thread_local_ cv_trace * g_trace_list =
&g_trace_footer_local;

static cv_trace_global * g_trace_global_list =
&g_trace_footer_global;

static cv_mutex g_trace_mutex = {0};

static cv_thread_local_ long i_recursive = 0;

static cv_thread_local_ char const * g_stack_table[8u];

static cv_thread_local_ long g_stack_index = 0;

static cv_thread_local_ cv_clock_mono g_profile_table[8u];

static cv_thread_local_ long g_profile_index = 0;

static cv_thread_local_ cv_trace_msg g_trace_msg = {0};

/*
 *
 */

static void cv_trace_register( cv_trace * p_trace ) {
    if (p_trace->p_local_next) {
    } else {
        p_trace->p_local_next = g_trace_list;
        g_trace_list = p_trace;
        /* Do register of tls */
        {
            void * p_specific;
            p_specific = cv_specific_get(&cv_trace_key);
            if (!p_specific) {
                static unsigned char a_specific[8u];
                cv_specific_set(&cv_trace_key, a_specific);
            }
        }
        /* Do register to global list */
        if (p_trace->p_global->p_global_next) {
        } else {
            cv_mutex_impl_lock(&g_trace_mutex);
            if (p_trace->p_global->p_global_next) {
            } else {
                p_trace->p_global->p_global_next = g_trace_global_list;
                g_trace_global_list = p_trace->p_global;
            }
            cv_mutex_impl_unlock(&g_trace_mutex);
        }
    }
}

/*
 *
 */

static void cv_trace_flush_cb(cv_trace * p_trace) {
    {
        cv_ull const i_local_elapsed = cv_clock_get(
            &p_trace->o_local_stats.o_elapsed);
        cv_ull const i_global_elapsed = cv_clock_get(
            &p_trace->p_global->o_global_stats.o_elapsed);
        cv_clock_set(&p_trace->p_global->o_global_stats.o_elapsed,
            i_global_elapsed + i_local_elapsed);
    }
    {
        cv_ull const i_local_count = cv_clock_counter_get(
            &p_trace->o_local_stats.o_count);
        cv_ull const i_global_count = cv_clock_counter_get(
            &p_trace->p_global->o_global_stats.o_count);
        cv_clock_counter_set(&p_trace->p_global->o_global_stats.o_count,
            i_global_count + i_local_count);
    }
    cv_clock_set(&p_trace->o_local_stats.o_elapsed, 0);
    cv_clock_counter_set(&p_trace->o_local_stats.o_count, 0);
}

/*
 *
 */

void cv_trace_flush(void);
void cv_trace_flush(void) {
    /* Merge of stats into global variables */
    cv_trace * p_iterator = g_trace_list;
    while (p_iterator && (p_iterator != &g_trace_footer_local)) {
        cv_trace_flush_cb(p_iterator);
        p_iterator = p_iterator->p_local_next;
    }

}

/*
 *
 */

static void cv_trace_update_stack( cv_trace * p_trace, unsigned char i_type) {
    unsigned char const i_level = p_trace->p_global->i_level;
    if (cv_trace_test_stack_level(i_level)) {
        if (cv_trace_type_func_enter == i_type) {
            if ((g_stack_index >= 0) && (g_stack_index < 8)) {
                g_stack_table[g_stack_index] = p_trace->p_global->pc_text;
            }
            g_stack_index ++;
        } else if (cv_trace_type_func_leave == i_type) {
            if (g_stack_index > 0) {
                g_stack_index --;
            }
        }
    }
}

/*
 *
 */

static void cv_trace_update_profile( cv_trace * p_trace,
    unsigned char i_type) {
    unsigned char const i_level = p_trace->p_global->i_level;
    if (cv_trace_test_profile_level(i_level)) {
        cv_trace_register(p_trace);
        if (cv_trace_type_func_enter == i_type) {
            if ((g_profile_index >= 0) && (g_profile_index < 8)) {
                g_profile_table[g_profile_index] = g_trace_msg.o_clock_mono;
            }
            g_profile_index ++;
        } else if (cv_trace_type_func_leave == i_type) {
            /* Calculate elapsed time */
            if (g_profile_index > 0) {
                g_profile_index --;
                if ((g_profile_index >= 0) && (g_profile_index < 8)) {
                    cv_clock_duration o_duration = {0};
                    cv_clock_counter_inc(&p_trace->o_local_stats.o_count);
                    if (0 < cv_clock_diff(&g_trace_msg.o_clock_mono.o_clock,
                        &(g_profile_table[g_profile_index].o_clock),
                        &o_duration)) {
                        cv_ull ll_elapsed = cv_clock_get(
                            &p_trace->o_local_stats.o_elapsed);
                        ll_elapsed += cv_clock_get(&o_duration.o_clock);
                        cv_clock_set(&p_trace->o_local_stats.o_elapsed,
                            ll_elapsed);
                    }
                }
            }
        } else if (cv_trace_type_event_signal == i_type) {
            cv_clock_counter_inc(&p_trace->o_local_stats.o_count);
        } else {
        }
    }
}

/*
 *
 */

void cv_trace_dispatch( cv_trace * p_trace, unsigned char i_type) {
    if (0 == (i_recursive++)) {
        /* mutex to protect list */
        /* link node into global list */
        /* read current clock */
        /* print of type */
        cv_debug_assert_(p_trace, cv_debug_code_null_ptr);
        g_trace_msg.p_local = p_trace;
        g_trace_msg.i_type = i_type;
        if (cv_clock_mono_read(&g_trace_msg.o_clock_mono)) {
            /* Stack processing */
            cv_trace_update_stack(p_trace, i_type);
            /* Update stats */
            /* process enter */
            /* process leave */
            /* process signal */
            cv_trace_update_profile(p_trace, i_type);
            cv_trace_msg_dispatch(&g_trace_msg);
        }
    } else {
        cv_debug_break_(cv_debug_code_recursive);
    }
    i_recursive --;
}

/*
 *
 */

long cv_trace_stack_query(
    char const * * p_buffer,
    long i_count_max) {
    long i_count = 0;
    long i_index = g_stack_index;
    if (i_index > 8) {
        i_index = 8;
    }
    while (i_index > 0) {
        i_index --;
        {
            char const * const p_trace_text = g_stack_table[i_index];
            if (i_count < i_count_max) {
                p_buffer[i_count] = p_trace_text;
                i_count ++;
            }
        }
    }
    return i_count;
}

/*
 *
 */

static void cv_trace_stack_report_cb(char const * p_trace_text) {
#if defined cv_have_libc_
    printf("[%s]\n", p_trace_text);
#else /* #if defined cv_have_libc_ */
    (void)(p_trace_text);
#endif /* #if defined cv_have_libc_ */
}

/*
 *
 */

void cv_trace_stack_report(void) {
    long i_index = g_stack_index;
    if (i_index > 8) {
        i_index = 8;
    }
    while (i_index > 0) {
        i_index --;
        cv_trace_stack_report_cb(g_stack_table[i_index]);
    }
}

/*
 *
 */

static void cv_trace_profile_report_cb(
    cv_trace_global * p_iterator) {
#if defined cv_have_libc_
    {
        cv_ull const ll_count = cv_clock_counter_get(
            &p_iterator->o_global_stats.o_count);
        unsigned long int const u_count = (ll_count & cv_unsigned_long_max_);
        cv_clock_usec o_clock_usec = {0};
        cv_clock_get_usec(&p_iterator->o_global_stats.o_elapsed,
            &o_clock_usec);
        printf("%10lu.%06lu:%lu:[%s]\n",
            o_clock_usec.i_seconds,
            o_clock_usec.i_useconds,
            u_count,
            p_iterator->pc_text);
    }
#else /* #if defined cv_have_libc_ */
    (void)(p_iterator);
#endif /* #if defined cv_have_libc_ */
}

/*
 *
 */

void cv_trace_profile_report(void) {
    cv_trace_flush();
    cv_trace_msg_local_flush();
    cv_trace_msg_global_flush();
    {
        cv_trace_global * p_iterator = g_trace_global_list;
        while (p_iterator && (p_iterator != &g_trace_footer_global)) {
            cv_trace_profile_report_cb(p_iterator);
            p_iterator = p_iterator->p_global_next;
        }
    }
}

/* end-of-file: cv_trace_node.c */
