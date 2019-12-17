/* See LICENSE for license details */

#ifndef cv_trace_func_h_
#define cv_trace_func_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_node.h>
#include <cv_misc/cv_function.h>

/*
 *
 */

struct cv_trace_func {
    cv_trace_node o_trace_node;
};

#define cv_trace_func_initializer_(level, name) \
{ cv_trace_node_initializer_(level, name) }

void cv_trace_func_enter(cv_trace_func * p_trace_func);
void cv_trace_func_leave(cv_trace_func * p_trace_func);

#endif /* #ifndef cv_trace_func_h_ */

/* end-of-file: cv_trace_func.h */
