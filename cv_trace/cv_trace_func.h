/* See LICENSE for license details */

#ifndef cv_trace_func_h_
#define cv_trace_func_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_node.h>

#define cv_trace_func_decl_(level, name) \
    cv_trace_decl_( \
        cv_trace_klass_func, level, name)

#define cv_trace_func_enter_(name) \
    cv_trace_enter_(name)

#define cv_trace_func_leave_(name) \
    cv_trace_leave_(name)

#define cv_trace_func0_decl_(name) \
    cv_trace_func_decl_( \
        cv_trace_level_0, name)

#define cv_trace_func0_enter_(name) \
    cv_trace_func_enter_(name)

#define cv_trace_func0_leave_(name) \
    cv_trace_func_leave_(name)

#define cv_trace_func1_decl_(name) \
    cv_trace_func_decl_( \
        cv_trace_level_1, name)

#define cv_trace_func1_enter_(name) \
    cv_trace_func_enter_(name)

#define cv_trace_func1_leave_(name) \
    cv_trace_func_leave_(name)

#define cv_trace_func2_decl_(name) \
    cv_trace_func_decl_( \
        cv_trace_level_2, name)

#define cv_trace_func2_enter_(name) \
    cv_trace_func_enter_(name)

#define cv_trace_func2_leave_(name) \
    cv_trace_func_leave_(name)

#define cv_trace_func3_decl_(name) \
    cv_trace_func_decl_( \
        cv_trace_level_3, name)

#define cv_trace_func3_enter_(name) \
    cv_trace_func_enter_(name)

#define cv_trace_func3_leave_(name) \
    cv_trace_func_leave_(name)

#define cv_trace_func4_decl_(name) \
    cv_trace_func_decl_( \
        cv_trace_level_4, name)

#define cv_trace_func4_enter_(name) \
    cv_trace_func_enter_(name)

#define cv_trace_func4_leave_(name) \
    cv_trace_func_leave_(name)

#define cv_trace_func5_decl_(name) \
    cv_trace_func_decl_( \
        cv_trace_level_5, name)

#define cv_trace_func5_enter_(name) \
    cv_trace_func_enter_(name)

#define cv_trace_func5_leave_(name) \
    cv_trace_func_leave_(name)

#define cv_trace_func6_decl_(name) \
    cv_trace_func_decl_( \
        cv_trace_level_6, name)

#define cv_trace_func6_enter_(name) \
    cv_trace_func_enter_(name)

#define cv_trace_func6_leave_(name) \
    cv_trace_func_leave_(name)

#define cv_trace_func7_decl_(name) \
    cv_trace_func_decl_( \
        cv_trace_level_7, name)

#define cv_trace_func7_enter_(name) \
    cv_trace_func_enter_(name)

#define cv_trace_func7_leave_(name) \
    cv_trace_func_leave_(name)

#endif /* #ifndef cv_trace_func_h_ */

/* end-of-file: cv_trace_func.h */
