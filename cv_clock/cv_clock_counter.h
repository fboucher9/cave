/* See LICENSE for license details */

#ifndef cv_clock_counter_h_
#define cv_clock_counter_h_

/*
 *
 */

#include <cv_clock/cv_clock_pred.h>
#include <cv_clock/cv_clock.h>

struct cv_clock_counter {
    cv_clock o_clock;
};

void cv_clock_counter_init( cv_clock_counter * p_this );

void cv_clock_counter_cleanup( cv_clock_counter * p_this );

cv_ull cv_clock_counter_get( cv_clock_counter const * p_this );

void cv_clock_counter_set( cv_clock_counter * p_this, cv_ull ll_value );

void cv_clock_counter_inc( cv_clock_counter * p_this );

void cv_clock_counter_dec( cv_clock_counter * p_this );

void cv_clock_counter_add( cv_clock_counter * p_this, unsigned long i_value );

void cv_clock_counter_sub( cv_clock_counter * p_this, unsigned long i_value );

#endif /* #ifndef cv_clock_counter_h_ */

/* end-of-file: cv_clock_counter.h */
