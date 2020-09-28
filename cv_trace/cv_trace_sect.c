/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_sect.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_runtime.h>

cv_debug_decl_(g_trace_sect_class, "cv_trace_sect", sizeof(cv_trace_sect));

static cv_thread_local_ cv_trace_sect * g_trace_sect_this = 0;

/*
 *
 */

void cv_trace_sect_init( cv_trace_sect * p_this,
    cv_array const * p_name, cv_array const * p_region, cv_bool b_echo) {
    cv_debug_construct_(g_trace_sect_class, p_this);
    cv_array_init_ref(&p_this->o_name, p_name);
    cv_array_init_ref(&p_this->o_region, p_region);
    cv_array_init_ref(&p_this->o_iterator, p_region);
    p_this->b_echo = b_echo;
}

/*
 *
 */

void cv_trace_sect_cleanup( cv_trace_sect * p_this) {
    p_this->b_echo = 0;
    cv_array_cleanup(&p_this->o_iterator);
    cv_array_cleanup(&p_this->o_region);
    cv_array_cleanup(&p_this->o_name);
    cv_debug_destruct_(g_trace_sect_class, p_this);
}

/*
 *
 */

void cv_trace_sect_begin( cv_trace_sect * p_this) {
    g_trace_sect_this = p_this;
    /* begin a new message in cache */
    /* setup the log header */
    /* grab copy of clock, pid, tid, tname, stack, sname */
    if (p_this->b_echo) {
        static char const g_colon[] = { ':' };
        int const i_stdout = cv_runtime_stdout_fileno();
        cv_runtime_write( i_stdout, p_this->o_name.o_min.pc_void,
            cv_array_len(&p_this->o_name));
        cv_runtime_write( i_stdout, g_colon, sizeof(g_colon) );
    }
}

/*
 *
 */

void cv_trace_sect_print( cv_array const * p_array) {
    /* append to current message */
    if (g_trace_sect_this) {
        cv_trace_sect * p_this = g_trace_sect_this;
        if (p_this->b_echo) {
            int const i_stdout = cv_runtime_stdout_fileno();
            cv_runtime_write( i_stdout, p_array->o_min.pc_void,
                cv_array_len(p_array));
        }
    }
}

/*
 *
 */

void cv_trace_sect_end(void) {
    /* flush of message cache */
    if (g_trace_sect_this) {
        cv_trace_sect * p_this = g_trace_sect_this;
        if (p_this->b_echo) {
            static char const g_newline[] = { '\n' };
            int const i_stdout = cv_runtime_stdout_fileno();
            cv_runtime_write( i_stdout, g_newline, sizeof(g_newline) );
        }
    }
    g_trace_sect_this = 0;
}

/* end-of-file: cv_trace_sect.h */
