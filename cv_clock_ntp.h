/* See LICENSE for license details */

#ifndef cv_clock_ntp_h_
#define cv_clock_ntp_h_

/*
 *
 */

#include <cv_clock.h>

/*
 *
 */

struct cv_clock_ntp {
    cv_clock o_clock;
};

#define cv_clock_ntp_initializer_ { cv_clock_initializer_ }

void cv_clock_ntp_init(
    cv_clock_ntp * p_this);

void cv_clock_ntp_cleanup(
    cv_clock_ntp * p_this);

cv_bool cv_clock_ntp_read(
    cv_clock_ntp * r_value);

cv_bool cv_clock_ntp_until(
    cv_clock_ntp const * p_value);

cv_bool cv_clock_ntp_info(
    cv_clock_ntp const * p_value,
    cv_clock_info * r_info);

#endif /* #ifndef cv_clock_ntp_h_ */

/* end-of-file: cv_clock_ntp.h */
