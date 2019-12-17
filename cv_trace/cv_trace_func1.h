/* See LICENSE for license details */

#ifndef cv_trace_func1_h_
#define cv_trace_func1_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_func.h>

#if (cv_trace_levels_ > 1)

/*
 *
 */

struct cv_trace_func1 {
    cv_trace_func o_trace_func;
};

#define cv_trace_func1_initializer_(func_name) \
{ cv_trace_func_initializer_(cv_trace_level_1, func_name) }

void xx_trace_func1_enter(cv_trace_func1 * p_trace_func1);
void xx_trace_func1_leave(cv_trace_func1 * p_trace_func1);

#define cv_trace_func1_decl_(var_name, func_name) \
static cv_trace_func1 var_name = cv_trace_func1_initializer_(func_name)
#define cv_trace_func1_enter_(name) xx_trace_func1_enter(&(name))
#define cv_trace_func1_leave_(name) xx_trace_func1_leave(&(name))

#else /* #if (cv_trace_levels_ > 1) */

#define cv_trace_func1_decl_(var_name) \
    static char var_name = cv_trace_level_1
#define cv_trace_func1_enter_(name) (void)(name)
#define cv_trace_func1_leave_(name) (void)(name)

#endif /* #if (cv_trace_levels_ > 1) */

#endif /* #ifndef cv_trace_func1_h_ */

/* end-of-file: cv_trace_func1.h */
