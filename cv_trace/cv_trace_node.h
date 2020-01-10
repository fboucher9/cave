/* See LICENSE for license details */

#ifndef cv_trace_node_h_
#define cv_trace_node_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_stats.h>
#include <cv_misc/cv_thread_local.h>

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

enum cv_trace_klass {
    cv_trace_klass_func = 1,
    cv_trace_klass_event
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

struct cv_trace_global_node {
    cv_trace_global_node * p_global_next;
    /* -- */
    cv_trace_stats o_global_stats;
    /* -- */
    char const * pc_text;
    /* -- */
    unsigned char i_klass;
    unsigned char i_level;
    unsigned char uc_padding[6u];
};

#define cv_trace_global_node_initializer_(klass, level, text) \
{ 0, cv_trace_stats_initializer_, (text), (klass), (level), {0} }

/*
 *
 */

struct cv_trace_local_node {
    cv_trace_local_node * p_local_next;
    /* -- */
    cv_trace_global_node * p_global_node;
    /* -- */
    cv_trace_stats o_local_stats;
};

#define cv_trace_local_node_initializer_(global_node) \
{ 0, &(global_node), cv_trace_stats_initializer_ }

#define cv_trace_node_decl_(type, level, name) \
static cv_trace_global_node g_trace_##name = \
cv_trace_global_node_initializer_( \
    (type), (level), #name); \
static cv_thread_local_ cv_trace_local_node l_trace_##name = \
cv_trace_local_node_initializer_(g_trace_##name)

void cv_trace_node_dispatch( cv_trace_local_node * p_trace_node,
    unsigned char i_type);

#define cv_trace_node_enter_(name) \
cv_trace_node_dispatch( \
    &(l_trace_##name), cv_trace_type_func_enter)

#define cv_trace_node_leave_(name) \
cv_trace_node_dispatch( \
    &(l_trace_##name), cv_trace_type_func_leave)

#define cv_trace_node_signal_(name) \
cv_trace_node_dispatch( \
    &(l_trace_##name), cv_trace_type_event_signal)

long cv_trace_node_stack_query(
    char const * * p_buffer,
    long i_count_max);

void cv_trace_node_stack_report(void);

void cv_trace_node_profile_report(void);

#endif /* #ifndef cv_trace_node_h_ */

/* end-of-file: cv_trace_node.h */
