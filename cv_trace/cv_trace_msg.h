/* See LICENSE for license details */

#ifndef cv_trace_msg_h_
#define cv_trace_msg_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_clock/cv_clock_mono.h>

/*
 *
 */

struct cv_trace_msg {
    cv_clock_mono o_clock_mono;
    /* -- */
    cv_trace_local_node * p_local_node;
    /* -- */
    unsigned char i_type;
    unsigned char uc_padding[7u];
};

#define cv_trace_msg_initializer_ \
{ cv_clock_mono_initializer_, 0, 0, {0} }

void cv_trace_msg_dispatch( cv_trace_msg * p_trace_msg);

#endif /* #ifndef cv_trace_msg_h_ */

/* end-of-file: cv_trace_msg.h */
