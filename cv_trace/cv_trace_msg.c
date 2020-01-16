/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_msg.h>
#include <cv_trace/cv_trace_node.h>
#include <cv_trace/cv_trace_level.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_runtime.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

static cv_thread_local_ cv_trace_msg * g_trace_msg_cache = 0;

static cv_thread_local_ unsigned int g_trace_msg_cache_index = 0;

/*
 *
 */

static void cv_trace_msg_flush_cb(cv_trace_msg * p_trace_msg) {
#if defined cv_have_libc_
    unsigned char const uc_level = p_trace_msg->p_local->p_global->i_level;
    unsigned short const us_level = uc_level;
    if (cv_trace_test_echo_level(uc_level)) {
        unsigned char const uc_type = p_trace_msg->i_type;
        cv_clock_usec o_value_usec = cv_clock_usec_initializer_;
        cv_clock_get_usec(&p_trace_msg->o_clock_mono.o_clock, &o_value_usec);
        fprintf(stdout, "%10ld.%06ld:%c%hu:[%s]\n", o_value_usec.i_seconds,
            o_value_usec.i_useconds,
            cv_trace_type_func_enter == uc_type ? '{' :
            cv_trace_type_func_leave == uc_type ? '}' : '!',
            us_level,
            p_trace_msg->p_local->p_global->pc_text);
    }

    /* Write message to log file(s) */
    if (cv_trace_test_log_level(uc_level)) {
        /* use environment for path of log file? */
        /* use pid to select log file instance? */
        /* open a log file for overwrite */
        /* lock of file for single process */
        /* set size of file */
        /* mmap of file */
    }

#else /* #if defined cv_have_libc_ */
    (void)(p_trace_msg);
#endif /* #if defined cv_have_libc_ */
}

/*
 *
 */

void cv_trace_msg_flush(void) {
    unsigned int i_cache_iterator = 0;
    while (i_cache_iterator < g_trace_msg_cache_index) {
        cv_trace_msg_flush_cb(g_trace_msg_cache + i_cache_iterator);
        i_cache_iterator ++;
    }
    g_trace_msg_cache_index = 0;
}

/*
 *
 */

void cv_trace_msg_dispatch( cv_trace_msg * p_trace_msg) {
    /* cache of messages per thread */
    /* allocate cache at first use */
    if (!g_trace_msg_cache) {
        g_trace_msg_cache = cv_runtime_malloc(30000u);
    }
    if (g_trace_msg_cache) {
        /* setup a timer for flush of cache */
        /* flush of cache when full */
        if (g_trace_msg_cache_index >= (30000u / sizeof(cv_trace_msg))) {
            /* flush... */
            cv_trace_msg_flush();
            cv_trace_msg_flush_cb(p_trace_msg);
        } else {
            g_trace_msg_cache[g_trace_msg_cache_index] = *p_trace_msg;
            g_trace_msg_cache_index ++;
        }
    }
}

/*
 *  Function: cv_trace_msg_thread_detach()
 *
 *  Description: Notification when thread has completed.  Free resources that
 *  have been allocated for the thread.
 *
 *  Parameters: None.
 *
 *  Returns: None.
 *
 *  Comments: This function must be called from a pthread_key_t destructor
 *  which is called from the context of the thread being terminated.
 */

void cv_trace_msg_thread_detach(void) {
    if (g_trace_msg_cache) {
        cv_runtime_free(g_trace_msg_cache);
        g_trace_msg_cache = 0;
    }
}

/* end-of-file: cv_trace_msg.c */
