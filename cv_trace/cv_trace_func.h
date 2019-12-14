/* See LICENSE for license details */

#ifndef cv_trace_func_h_
#define cv_trace_func_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_node.h>

#if (cv_trace_levels_ > 0)

/*
 *
 */

struct cv_trace_func {
    cv_trace_node o_trace_node;
};

#define cv_trace_func_initializer_(level) \
{ cv_trace_node_initializer_(level, cv_function_) }

void xx_trace_func_enter(cv_trace_func * p_trace_func);
void xx_trace_func_leave(cv_trace_func * p_trace_func);

#define cv_trace_func_decl_(name, level) \
static cv_trace_func name = cv_trace_func_initializer_(level)
#define cv_trace_func_enter_(name) xx_trace_func_enter(&(name))
#define cv_trace_func_leave_(name) xx_trace_func_leave(&(name))

#else /* #if (cv_trace_levels_ > 0) */

#define cv_trace_func_decl_(name, level) static char name = level
#define cv_trace_func_enter_(name) (void)(name)
#define cv_trace_func_leave_(name) (void)(name)

#endif /* #if (cv_trace_levels_ > 0) */

#endif /* #ifndef cv_trace_func_h_ */

/* end-of-file: cv_trace_func.h */
