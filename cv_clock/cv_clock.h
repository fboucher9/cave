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

void cv_clock_init( cv_clock * p_this);

void cv_clock_init_msec( cv_clock * p_this,
    unsigned long i_seconds, unsigned long i_mseconds);

void cv_clock_init_usec( cv_clock * p_this,
    unsigned long i_seconds, unsigned long i_useconds);

void cv_clock_init_nsec( cv_clock * p_this,
    unsigned long i_seconds, unsigned long i_nseconds);

void cv_clock_cleanup( cv_clock * p_this);

cv_bool cv_clock_read( cv_clock * p_this, int e_epoch);

cv_bool cv_clock_until( cv_clock const * p_this, int e_epoch);

cv_bool cv_clock_query( cv_clock const * p_this,
    int e_epoch, cv_clock_info * r_info);

#endif /* #ifndef cv_clock_h_ */

/* end-of-file: cv_clock.h */
