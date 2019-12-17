/* See LICENSE for license details */

#include <cv_trace/cv_trace_func1.h>

#if (cv_trace_levels_ > 1)

/*
 *
 */

void xx_trace_func1_enter(cv_trace_func1 * p_trace_func1) {
    cv_trace_func_enter(&p_trace_func1->o_trace_func);
}

/*
 *
 */

void xx_trace_func1_leave(cv_trace_func1 * p_trace_func1) {
    cv_trace_func_leave(&p_trace_func1->o_trace_func);
}

#endif /* #if (cv_trace_levels_ > 1) */

/* end-of-file: cv_trace_func1.h */
