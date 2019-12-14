/* See LICENSE for license details */

#include <cv_trace/cv_trace_func0.h>

#if (cv_trace_levels_ > 0)

/*
 *
 */

void xx_trace_func0_enter(cv_trace_func0 * p_trace_func0) {
    cv_trace_func_enter(&p_trace_func0->o_trace_func);
}

/*
 *
 */

void xx_trace_func0_leave(cv_trace_func0 * p_trace_func0) {
    cv_trace_func_leave(&p_trace_func0->o_trace_func);
}

#endif /* #if (cv_trace_levels_ > 0) */

/* end-of-file: cv_trace_func0.h */
