/* See LICENSE for license details */

#ifndef cv_trace_func_h_
#define cv_trace_func_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_node.h>

#define cv_trace_func_decl_(level, name) \
    cv_trace_node_decl_( \
        cv_trace_type_func_enter, level, name)

#define cv_trace_func_enter_(name) \
    cv_trace_node_enter_(name)

#define cv_trace_func_leave_(name) \
    cv_trace_node_leave_(name)

#if (cv_trace_levels_ > 0)

#define cv_trace_func0_decl_(func_name) \
    cv_trace_func_decl_( \
        cv_trace_level_0, func_name)

#define cv_trace_func0_enter_(func_name) \
    cv_trace_func_enter_(func_name)

#define cv_trace_func0_leave_(func_name) \
    cv_trace_func_leave_(func_name)

#else /* #if (cv_trace_levels_ > 0) */

#define cv_trace_func0_decl_(func_name) \
    static char l_trace_##func_name = cv_trace_level_0

#define cv_trace_func0_enter_(func_name) \
    (void)(l_trace_##func_name)

#define cv_trace_func0_leave_(func_name) \
    (void)(l_trace_##func_name)

#endif /* #if (cv_trace_levels_ > 0) */

#endif /* #ifndef cv_trace_func_h_ */

/* end-of-file: cv_trace_func.h */
