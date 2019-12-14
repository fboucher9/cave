/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_func.h>

/*
 *
 */

void cv_trace_func_enter(cv_trace_func * p_trace_func) {
    cv_trace_node_dispatch(&p_trace_func->o_trace_node,
        cv_trace_type_func_enter);
}

/*
 *
 */

void cv_trace_func_leave(cv_trace_func * p_trace_func) {
    cv_trace_node_dispatch(&p_trace_func->o_trace_node,
        cv_trace_type_func_leave);
}

/* end-of-file: cv_trace_func.c */
