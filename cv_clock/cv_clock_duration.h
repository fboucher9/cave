/* See LICENSE for license details */

#ifndef cv_clock_duration_h_
#define cv_clock_duration_h_

/*
 *
 */

#include <cv_clock/cv_clock.h>

/*
 *
 */

struct cv_clock_duration {
    cv_clock o_clock;
};

void cv_clock_duration_init( cv_clock_duration * p_this);

void cv_clock_duration_init_msec( cv_clock_duration * p_this,
    unsigned long i_seconds, unsigned long i_mseconds);

void cv_clock_duration_init_usec( cv_clock_duration * p_this,
    unsigned long i_seconds, unsigned long i_useconds);

void cv_clock_duration_init_nsec( cv_clock_duration * p_this,
    unsigned long i_seconds, unsigned long i_nseconds);

void cv_clock_duration_cleanup( cv_clock_duration * p_this);

cv_bool cv_clock_duration_until( cv_clock_duration const * p_this);

#if 0 /* not used yet */
cv_bool cv_clock_duration_info( cv_clock_duration const * p_this,
    cv_clock_info * r_info);
#endif /* not used yet */

cv_bool cv_clock_duration_min( cv_clock_duration const * p_left,
    cv_clock_duration const * p_right, cv_clock_duration * r_result);

#endif /* #ifndef cv_clock_duration_h_ */

/* end-of-file: cv_clock_duration.h */
