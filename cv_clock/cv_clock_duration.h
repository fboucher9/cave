/* See LICENSE for license details */

#ifndef cv_clock_duration_h_
#define cv_clock_duration_h_

/*
 *
 */

#include <cv_clock.h>

/*
 *
 */

struct cv_clock_duration {
    cv_clock o_clock;
};

#define cv_clock_duration_initializer_ { cv_clock_initializer_ }

void cv_clock_duration_init(
    cv_clock_duration * p_this);

void cv_clock_duration_cleanup(
    cv_clock_duration * p_this);

cv_bool cv_clock_duration_until(
    cv_clock_duration const * p_this);

cv_bool cv_clock_duration_info(
    cv_clock_duration const * p_this,
    cv_clock_info * r_info);

#endif /* #ifndef cv_clock_duration_h_ */

/* end-of-file: cv_clock_duration.h */
