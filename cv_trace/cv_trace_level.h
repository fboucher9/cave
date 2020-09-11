/* See LICENSE for license details */

#ifndef cv_trace_level_h_
#define cv_trace_level_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_sect.h>

enum cv_trace_level_const {
    cv_trace_level_error = 0,
    cv_trace_level_warning,
    cv_trace_level_info,
    cv_trace_level_verbose,
    cv_trace_level_process,
    cv_trace_level_thread,
    cv_trace_level_summary,
    cv_trace_level_period,
    cv_trace_level_debug,
    cv_trace_level_max
};

struct cv_trace_level {
    cv_trace_sect a_level[cv_trace_level_max];
};

cv_bool cv_trace_level_init(
    cv_trace_level * p_this,
    unsigned long i_echo_flags);

void cv_trace_level_cleanup(
    cv_trace_level * p_this);

cv_trace_sect * cv_trace_level_get(
    cv_trace_level * p_this,
    int e_trace_level);

#endif /* #ifndef cv_trace_level_h_ */

/* end-of-file: cv_trace_level.h */
