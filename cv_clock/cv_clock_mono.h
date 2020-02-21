/* See LICENSE for license details */

#ifndef cv_clock_mono_h_
#define cv_clock_mono_h_

/*
 *
 */

#include <cv_clock/cv_clock.h>

/*
 *
 */

struct cv_clock_mono {
    cv_clock o_clock;
};

void cv_clock_mono_init(
    cv_clock_mono * p_this);

void cv_clock_mono_cleanup(
    cv_clock_mono * p_this);

cv_bool cv_clock_mono_read(
    cv_clock_mono * p_this);

cv_bool cv_clock_mono_until(
    cv_clock_mono const * p_this);

cv_bool cv_clock_mono_info(
    cv_clock_mono const * p_this,
    cv_clock_info * r_info);

int cv_clock_mono_diff( cv_clock_mono const * p_left,
    cv_clock_mono const * p_right, cv_clock_duration * r_duration);

#endif /* #ifndef cv_clock_mono_h_ */

/* end-of-file: cv_clock_mono.h */
