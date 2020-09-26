/* See LICENSE for license details */

#ifndef cv_stopwatch_tick_h_
#define cv_stopwatch_tick_h_

/*
 *
 */

#include <cv_clock/cv_clock_pred.h>
#include <cv_clock/cv_clock_tick.h>

/*
 *
 */

struct cv_stopwatch_tick {
    cv_clock_tick o_accumulator;
};

void cv_stopwatch_tick_init( cv_stopwatch_tick * p_this );
void cv_stopwatch_tick_cleanup( cv_stopwatch_tick * p_this );
void cv_stopwatch_tick_start( cv_stopwatch_tick * p_this );
void cv_stopwatch_tick_stop( cv_stopwatch_tick * p_this );

#endif /* #ifndef cv_stopwatch_tick_h_ */

/* end-of-file: cv_stopwatch_tick.h */
