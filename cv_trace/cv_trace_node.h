/* See LICENSE for license details */

#ifndef cv_trace_node_h_
#define cv_trace_node_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_stats.h>
#include <cv_misc/cv_null.h>

/*
 *
 */

enum cv_trace_type {
    cv_trace_type_func_enter = 1,
    cv_trace_type_func_leave,
    cv_trace_type_event_signal
};

/*
 *
 */

enum cv_trace_level {
    cv_trace_level_0 = 0,
    cv_trace_level_1,
    cv_trace_level_2,
    cv_trace_level_3,
    cv_trace_level_4,
    cv_trace_level_5,
    cv_trace_level_6,
    cv_trace_level_7
};

/*
 *
 */

struct cv_trace_node {
    cv_trace_node * p_next;
    /* -- */
    char const * pc_text;
    /* -- */
    unsigned char i_level;
    unsigned char uc_padding[7u];
    /* -- */
    cv_trace_stats o_trace_stats;
};

#define cv_trace_node_initializer_(level, text) \
{ cv_null_, (text), (level), {0}, cv_trace_stats_initializer_ }

void cv_trace_node_dispatch( cv_trace_node * p_trace_node,
    unsigned char i_type);

void cv_trace_node_stack_report(void);

void cv_trace_node_profile_report(void);

#endif /* #ifndef cv_trace_node_h_ */

/* end-of-file: cv_trace_node.h */
