/* See LICENSE for license details */

#ifndef cv_clock_h_
#define cv_clock_h_

/*
 *
 */

#include <cv_clock/cv_clock_pred.h>
#include <cv_clock/cv_clock_epoch.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

/*
 *
 */

struct cv_clock {
    unsigned long i_seconds;
    unsigned long i_fraction;
};

#define cv_clock_initializer_ { 0, 0 }

void cv_clock_init( cv_clock * p_this);

void cv_clock_cleanup( cv_clock * p_this);

cv_bool cv_clock_read( cv_clock * p_this, int e_epoch);

cv_bool cv_clock_until( cv_clock const * p_this, int e_epoch);

cv_bool cv_clock_get_info( cv_clock const * p_this,
    int e_epoch, cv_clock_info * r_info);

cv_ull cv_clock_get( cv_clock const * p_this);

void cv_clock_set( cv_clock * p_this, cv_ull ll_value);

int cv_clock_diff( cv_clock const * p_left, cv_clock const * p_right,
    cv_clock_duration * r_duration);

#endif /* #ifndef cv_clock_h_ */