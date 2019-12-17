/* See LICENSE for license details */

#ifndef cv_trace_func2_h_
#define cv_trace_func2_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_func.h>

#if (cv_trace_levels_ > 2)

/*
 *
 */

struct cv_trace_func2 {
    cv_trace_func o_trace_func;
};

#define cv_trace_func2_initializer_(func_name) \
{ cv_trace_func_initializer_(cv_trace_level_2, func_name) }

void xx_trace_func2_enter(cv_trace_func2 * p_trace_func2);
void xx_trace_func2_leave(cv_trace_func2 * p_trace_func2);

#define cv_trace_func2_decl_(var_name, func_name) \
static cv_trace_func2 var_name = cv_trace_func2_initializer_(func_name)
#define cv_trace_func2_enter_(name) xx_trace_func2_enter(&(name))
#define cv_trace_func2_leave_(name) xx_trace_func2_leave(&(name))

#else /* #if (cv_trace_levels_ > 2) */

#define cv_trace_func2_decl_(var_name) \
    static char var_name = cv_trace_level_2
#define cv_trace_func2_enter_(name) (void)(name)
#define cv_trace_func2_leave_(name) (void)(name)

#endif /* #if (cv_trace_levels_ > 2) */

#endif /* #ifndef cv_trace_func2_h_ */

/* end-of-file: cv_trace_func2.h */
