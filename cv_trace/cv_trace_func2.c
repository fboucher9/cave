/* See LICENSE for license details */

#include <cv_trace/cv_trace_func2.h>

#if (cv_trace_levels_ > 2)

/*
 *
 */

void xx_trace_func2_enter(cv_trace_func2 * p_trace_func2) {
    cv_trace_func_enter(&p_trace_func2->o_trace_func);
}

/*
 *
 */

void xx_trace_func2_leave(cv_trace_func2 * p_trace_func2) {
    cv_trace_func_leave(&p_trace_func2->o_trace_func);
}

#endif /* #if (cv_trace_levels_ > 2) */

/* end-of-file: cv_trace_func2.h */
