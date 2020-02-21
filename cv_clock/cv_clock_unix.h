/* See LICENSE for license details */

#ifndef cv_clock_unix_h_
#define cv_clock_unix_h_

/*
 *
 */

#include <cv_clock/cv_clock.h>

/*
 *
 */

struct cv_clock_unix {
    cv_clock o_clock;
};

void cv_clock_unix_init(
    cv_clock_unix * p_this);

void cv_clock_unix_cleanup(
    cv_clock_unix * p_this);

cv_bool cv_clock_unix_read(
    cv_clock_unix * r_value);

cv_bool cv_clock_unix_until(
    cv_clock_unix const * p_value);

cv_bool cv_clock_unix_info(
    cv_clock_unix const * p_value,
    cv_clock_info * r_info);

#endif /* #ifndef cv_clock_unix_h_ */

/* end-of-file: cv_clock_unix.h */
