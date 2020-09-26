/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_stopwatch_tick.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_clock/cv_clock_tool.h>

/*
 *
 */

void cv_stopwatch_tick_init( cv_stopwatch_tick * p_this ) {
    cv_clock_tick_init(&p_this->o_accumulator);
}

/*
 *
 */

void cv_stopwatch_tick_cleanup( cv_stopwatch_tick * p_this ) {
    cv_clock_tick_cleanup(&p_this->o_accumulator);
}

/*
 *
 */

void cv_stopwatch_tick_start( cv_stopwatch_tick * p_this ) {
    cv_clock_tick o_tick_value;
    cv_clock_tick_init(&o_tick_value);
    if (cv_clock_tick_read(&o_tick_value)) {
        cv_clock_sub(&p_this->o_accumulator.o_clock,
            &o_tick_value.o_clock,
            &p_this->o_accumulator.o_clock);
    }
    cv_clock_tick_cleanup(&o_tick_value);
}

/*
 *
 */

void cv_stopwatch_tick_stop( cv_stopwatch_tick * p_this ) {
    cv_clock_tick o_tick_value;
    cv_clock_tick_init(&o_tick_value);
    if (cv_clock_tick_read(&o_tick_value)) {
        cv_clock_add(&p_this->o_accumulator.o_clock,
            &o_tick_value.o_clock,
            &p_this->o_accumulator.o_clock);
    }
    cv_clock_tick_cleanup(&o_tick_value);
}

/* end-of-file: cv_stopwatch_tick.c */
