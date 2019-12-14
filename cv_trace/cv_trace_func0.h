/* See LICENSE for license details */

#ifndef cv_trace_func0_h_
#define cv_trace_func0_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_func.h>

#if (cv_trace_levels_ > 0)

/*
 *
 */

struct cv_trace_func0 {
    cv_trace_func o_trace_func;
};

void xx_trace_func0_enter(cv_trace_func0 * p_trace_func0);
void xx_trace_func0_leave(cv_trace_func0 * p_trace_func0);

#define cv_trace_func0_decl_(name) \
static cv_trace_func0 name = { cv_trace_func_initializer_(cv_trace_level_0) };
#define cv_trace_func0_enter_(name) xx_trace_func0_enter(&(name))
#define cv_trace_func0_leave(name) xx_trace_func0_leave(&(name))

#else /* #if (cv_trace_levels_ > 0) */

#define cv_trace_func0_decl_(name) static char name = cv_trace_level_0
#define cv_trace_func0_enter_(name) (void)(name)
#define cv_trace_func0_leave_(name) (void)(name)

#endif /* #if (cv_trace_levels_ > 0) */

#endif /* #ifndef cv_trace_func0_h_ */

/* end-of-file: cv_trace_func0.h */
