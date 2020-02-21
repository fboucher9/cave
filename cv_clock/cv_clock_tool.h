/* See LICENSE for license details */

#ifndef cv_clock_tool_h_
#define cv_clock_tool_h_

/*
 *
 */

#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_duration.h>

/*
 *
 */

struct cv_clock_msec {
    unsigned long i_seconds;
    unsigned long i_mseconds;
};

/*
 *
 */

struct cv_clock_usec {
    unsigned long i_seconds;
    unsigned long i_useconds;
};

/*
 *
 */

struct cv_clock_nsec {
    unsigned long i_seconds;
    unsigned long i_nseconds;
};

cv_ull cv_clock_get( cv_clock const * p_this);

void cv_clock_get_msec( cv_clock const * p_this,
    cv_clock_msec * r_clock_msec);

void cv_clock_get_usec( cv_clock const * p_this,
    cv_clock_usec * r_clock_usec);

void cv_clock_get_nsec( cv_clock const * p_this,
    cv_clock_nsec * r_clock_nsec);

void cv_clock_set( cv_clock * p_this, cv_ull ll_value);

void cv_clock_set_msec( cv_clock * p_this,
    cv_clock_msec const * p_clock_msec);

void cv_clock_set_usec( cv_clock * p_this,
    cv_clock_usec const * p_clock_usec);

void cv_clock_set_nsec( cv_clock * p_this,
    cv_clock_nsec const * p_clock_nsec);

unsigned long cv_clock_to_fraction( unsigned long i_count,
    unsigned long i_freq);

unsigned long cv_clock_from_fraction( unsigned long i_fraction,
    unsigned long i_freq);

int cv_clock_diff( cv_clock const * p_left, cv_clock const * p_right,
    cv_clock_duration * r_duration);

cv_bool cv_clock_convert(
    cv_clock const * p_src_clock,
    int i_src_epoch,
    cv_clock * p_dst_clock,
    int i_dst_epoch);

#endif /* #ifndef cv_clock_tool_h_ */

/* end-of-file: cv_clock_tool.h */
