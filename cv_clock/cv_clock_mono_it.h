/* See LICENSE for license details */

#ifndef cv_clock_mono_it_h_
#define cv_clock_mono_it_h_

/*
 *
 */

#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_mono.h>

/*
 *
 */

struct cv_clock_mono_it {
    cv_clock_mono o_target;
};

#define cv_clock_mono_it_initializer_ { cv_clock_mono_initializer_ }

void cv_clock_mono_it_init( cv_clock_mono_it * p_this,
    cv_clock_mono const * p_target);

void cv_clock_mono_it_cleanup( cv_clock_mono_it * p_this);

cv_bool cv_clock_mono_it_next( cv_clock_mono_it * p_this,
    cv_clock_duration const * p_max_sleep);

#endif /* #ifndef cv_clock_mono_it_h_ */

/* end-of-file: cv_clock_mono_it.h */
