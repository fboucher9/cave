/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_msg.h>
#include <cv_trace/cv_trace_node.h>
#include <cv_clock/cv_clock_tool.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

/*
 *
 */

void cv_trace_msg_dispatch( cv_trace_msg * p_trace_msg) {
    unsigned char const uc_type = p_trace_msg->i_type;
    unsigned short const us_level = p_trace_msg->p_trace_node->i_level;
    cv_clock_usec o_value_usec = cv_clock_usec_initializer_;
    cv_clock_get_usec(&p_trace_msg->o_clock_mono.o_clock, &o_value_usec);
#if defined cv_have_libc_
    fprintf(stdout, "%10ld.%06ld:%c%hu:[%s]\n", o_value_usec.i_seconds,
        o_value_usec.i_useconds,
        cv_trace_type_func_enter == uc_type ? '{' :
        cv_trace_type_func_leave == uc_type ? '}' : '!',
        us_level,
        p_trace_msg->p_trace_node->pc_text);
#else /* #if defined cv_have_libc_ */
    cv_unused_(us_type);
#endif /* #if defined cv_have_libc_ */
}

/* end-of-file: cv_trace_msg.c */
