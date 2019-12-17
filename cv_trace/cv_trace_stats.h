/* See LICENSE for license details */

#ifndef cv_trace_stats_h_
#define cv_trace_stats_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_counter.h>

struct cv_trace_stats {
    cv_clock o_elapsed;
    cv_clock_counter o_count;
};

#define cv_trace_stats_initializer_ \
{ cv_clock_initializer_, cv_clock_counter_initializer_ }

#endif /* #ifndef cv_trace_stats_h_ */

/* end-of-file: cv_trace_stats.h */
