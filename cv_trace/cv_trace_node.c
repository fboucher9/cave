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
#include <cv_thread/cv_mutex.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_trace/cv_trace_msg.h>
#include <cv_clock/cv_clock_duration.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

#if defined cv_have_pthread_
#include <pthread.h>
extern pthread_key_t cv_trace_key;
#endif /* #if defined cv_have_pthread_ */

static cv_trace_global_node g_trace_footer_global_node =
cv_trace_global_node_initializer_(cv_trace_type_func_enter,
    cv_trace_level_0, "dummy");

static cv_trace_local_node g_trace_footer_local_node =
cv_trace_local_node_initializer_(g_trace_footer_global_node);

static cv_thread_local_ cv_trace_local_node * g_trace_list =
&g_trace_footer_local_node;

#if 0
static cv_mutex g_trace_mutex = cv_mutex_initializer_;
#endif

static cv_thread_local_ long i_recursive = 0;

static cv_thread_local_ cv_trace_msg g_trace_stack[8u];

static cv_thread_local_ long g_trace_stack_index = 0;

/*
 *
 */

static void cv_trace_node_register( cv_trace_local_node * p_trace_node ) {
    if (p_trace_node->p_local_next) {
    } else {
        p_trace_node->p_local_next = g_trace_list;
        g_trace_list = p_trace_node;
    }
}

/*
 *
 */

void cv_trace_node_dispatch( cv_trace_local_node * p_trace_node,
    unsigned char i_type) {
    /* Do register of tls */
#if defined cv_have_pthread_
    {
        void * p_specific;
        p_specific = pthread_getspecific(cv_trace_key);
        if (!p_specific) {
            static unsigned char a_specific[8u];
            pthread_setspecific(cv_trace_key, a_specific);
        }
    }
#endif /* #if defined cv_have_pthread_ */
    if (0 == (i_recursive++)) {
        /* mutex to protect list */
        /* link node into global list */
        /* read current clock */
        /* print of type */
        cv_trace_msg * p_trace_msg = 0;
        cv_debug_assert_(p_trace_node, cv_debug_code_null_ptr);
        if (cv_trace_type_func_enter == i_type) {
            if ((g_trace_stack_index >= 0) && (g_trace_stack_index < 8)) {
                p_trace_msg = g_trace_stack + g_trace_stack_index;
            }
            g_trace_stack_index ++;
        } else if (cv_trace_type_func_leave == i_type) {
            if (g_trace_stack_index > 0) {
                g_trace_stack_index --;
                if (g_trace_stack_index < 8) {
                    p_trace_msg = g_trace_stack + g_trace_stack_index;
                }
            }
        } else if (cv_trace_type_event_signal == i_type) {
            if ((g_trace_stack_index >= 0) && (g_trace_stack_index < 8)) {
                p_trace_msg = g_trace_stack + g_trace_stack_index;
            }
            g_trace_stack_index ++;
        } else {
            p_trace_msg = 0;
        }
        /* Update stats */
        /* process enter */
        /* process leave */
        /* process signal */
        if (p_trace_msg) {
            cv_clock_mono o_now = cv_clock_mono_initializer_;
            if (cv_clock_mono_read(&o_now)) {
#if 0
                cv_mutex_impl_lock(&g_trace_mutex);
#endif
                cv_trace_node_register(p_trace_node);
                if (cv_trace_type_func_enter == i_type) {
                } else if (cv_trace_type_func_leave == i_type) {
                    /* Calculate elapsed time */
                    cv_clock_duration o_duration =
                        cv_clock_duration_initializer_;
                    cv_clock_counter_inc(&p_trace_node->o_local_stats.o_count);
                    if (0 < cv_clock_diff(&o_now.o_clock,
                        &p_trace_msg->o_clock_mono.o_clock,
                        &o_duration)) {
                        cv_ull ll_elapsed = cv_clock_get(
                            &p_trace_node->o_local_stats.o_elapsed);
                        ll_elapsed += cv_clock_get(&o_duration.o_clock);
                        cv_clock_set(&p_trace_node->o_local_stats.o_elapsed,
                            ll_elapsed);
                    }
                } else if (cv_trace_type_event_signal == i_type) {
                    cv_clock_counter_inc(&p_trace_node->o_local_stats.o_count);
                } else {
                }
#if 0
                cv_mutex_impl_unlock(&g_trace_mutex);
#endif
                p_trace_msg->o_clock_mono = o_now;
                p_trace_msg->p_local_node = p_trace_node;
                p_trace_msg->i_type = i_type;
                cv_trace_msg_dispatch(p_trace_msg);
            }
        } else {
            cv_debug_msg_(cv_debug_code_error);
        }
    } else {
        cv_debug_break_(cv_debug_code_recursive);
    }
    i_recursive --;
}

/*
 *
 */

long cv_trace_node_stack_query(
    char const * * p_buffer,
    long i_count_max) {
    long i_count = 0;
    long i_index = g_trace_stack_index;
    if (i_index > 8) {
        i_index = 8;
    }
    while (i_index > 0) {
        i_index --;
        {
            cv_trace_msg const * const p_trace_msg = g_trace_stack + i_index;
            if (i_count < i_count_max) {
                p_buffer[i_count] = p_trace_msg->p_local_node->p_global_node->pc_text;
                i_count ++;
            }
        }
    }
    return i_count;
}

/*
 *
 */

static void cv_trace_node_stack_report_cb(cv_trace_msg const * p_trace_msg) {
#if defined cv_have_libc_
    printf("[%s]\n", p_trace_msg->p_local_node->p_global_node->pc_text);
#else /* #if defined cv_have_libc_ */
    (void)(p_trace_msg);
#endif /* #if defined cv_have_libc_ */
}

/*
 *
 */

void cv_trace_node_stack_report(void) {
    long i_index = g_trace_stack_index;
    if (i_index > 8) {
        i_index = 8;
    }
    while (i_index > 0) {
        i_index --;
        {
            cv_trace_msg const * const p_trace_msg = g_trace_stack + i_index;
            cv_trace_node_stack_report_cb(p_trace_msg);
        }
    }
}

/*
 *
 */

static void cv_trace_node_profile_report_cb(
    cv_trace_local_node * p_iterator) {
#if defined cv_have_libc_
    {
        cv_ull const ll_count = cv_clock_counter_get(
            &p_iterator->o_local_stats.o_count);
        unsigned long int const u_count = (ll_count & cv_unsigned_long_max_);
        cv_clock_usec o_clock_usec = cv_clock_usec_initializer_;
        cv_clock_get_usec(&p_iterator->o_local_stats.o_elapsed,
            &o_clock_usec);
        printf("%10lu.%06lu:%lu:[%s]\n",
            o_clock_usec.i_seconds,
            o_clock_usec.i_useconds,
            u_count,
            p_iterator->p_global_node->pc_text);
    }
#else /* #if defined cv_have_libc_ */
    (void)(p_iterator);
#endif /* #if defined cv_have_libc_ */
}

/*
 *
 */

void cv_trace_node_profile_report(void) {
    cv_trace_local_node * p_iterator = g_trace_list;
    while (p_iterator && (p_iterator != &g_trace_footer_local_node)) {
        cv_trace_node_profile_report_cb(p_iterator);
        p_iterator = p_iterator->p_local_next;
    }
}

/* end-of-file: cv_trace_node.c */
