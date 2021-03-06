/* See LICENSE for license details */

#ifndef cv_clock_it_h_
#define cv_clock_it_h_

/*
 *
 */

#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_mono.h>
#include <cv_clock/cv_clock_unix.h>

/*
 *
 */

struct cv_clock_it {
    cv_clock o_target;
    /* -- */
    int /* cv_clock_epoch */ i_epoch;
    int i_padding[3u];
};

void cv_clock_it_init( cv_clock_it * p_this,
    cv_clock const * p_target, int i_epoch);

void cv_clock_it_cleanup( cv_clock_it * p_this);

cv_bool cv_clock_it_next( cv_clock_it * p_this,
    cv_clock_duration const * p_max_sleep);

/*
 *
 */

struct cv_clock_unix_it {
    cv_clock_unix o_target;
};

void cv_clock_unix_it_init( cv_clock_unix_it * p_this,
    cv_clock_unix const * p_target);

void cv_clock_unix_it_cleanup( cv_clock_unix_it * p_this);

cv_bool cv_clock_unix_it_next( cv_clock_unix_it * p_this,
    cv_clock_duration const * p_max_sleep);

#endif /* #ifndef cv_clock_it_h_ */

/* end-of-file: cv_clock_it.h */
