/* See LICENSE for license details */

#include <cv_clock/cv_clock_tool.h>
#include <cv_debug.h>
#include <cv_misc/cv_limits.h>

/*
 *
 */

cv_ull cv_clock_get( cv_clock const * p_this) {
    cv_ull ll_result = 0;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    ll_result = p_this->i_seconds;
    ll_result <<= 32u;
    ll_result += p_this->i_fraction;
    return ll_result;
}

void cv_clock_get_msec( cv_clock const * p_this,
    cv_clock_msec * r_clock_msec) {
    cv_debug_assert_(p_this && r_clock_msec, cv_debug_code_null_ptr);
    r_clock_msec->i_seconds = p_this->i_seconds;
    r_clock_msec->i_mseconds = cv_clock_from_fraction(
        p_this->i_fraction, 1000ul);
}

void cv_clock_get_usec( cv_clock const * p_this,
    cv_clock_usec * r_clock_usec) {
    cv_debug_assert_(p_this && r_clock_usec, cv_debug_code_null_ptr);
    r_clock_usec->i_seconds = p_this->i_seconds;
    r_clock_usec->i_useconds = cv_clock_from_fraction(
        p_this->i_fraction, 1000000ul);
}

void cv_clock_get_nsec( cv_clock const * p_this,
    cv_clock_nsec * r_clock_nsec) {
    cv_debug_assert_(p_this && r_clock_nsec, cv_debug_code_null_ptr);
    r_clock_nsec->i_seconds = p_this->i_seconds;
    r_clock_nsec->i_nseconds = cv_clock_from_fraction(
        p_this->i_fraction, 1000000000ul);
}

/*
 *
 */

void cv_clock_set( cv_clock * p_this, cv_ull ll_value) {
    cv_ull ll_seconds = (ll_value >> 32u);
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    p_this->i_seconds = (ll_seconds & cv_unsigned_long_max_);
    p_this->i_fraction = (ll_value & cv_unsigned_long_max_);
}

void cv_clock_set_msec( cv_clock * p_this,
    cv_clock_msec const * p_clock_msec) {
    cv_debug_assert_(p_this && p_clock_msec, cv_debug_code_null_ptr);
    p_this->i_seconds = p_clock_msec->i_seconds;
    p_this->i_fraction = cv_clock_to_fraction(
        p_clock_msec->i_mseconds, 1000ul);
}

void cv_clock_set_usec( cv_clock * p_this,
    cv_clock_usec const * p_clock_usec) {
    cv_debug_assert_(p_this && p_clock_usec, cv_debug_code_null_ptr);
    p_this->i_seconds = p_clock_usec->i_seconds;
    p_this->i_fraction = cv_clock_to_fraction(
        p_clock_usec->i_useconds, 1000000ul);
}

void cv_clock_set_nsec( cv_clock * p_this,
    cv_clock_nsec const * p_clock_nsec) {
    cv_debug_assert_(p_this && p_clock_nsec, cv_debug_code_null_ptr);
    p_this->i_seconds = p_clock_nsec->i_seconds;
    p_this->i_fraction = cv_clock_to_fraction(
        p_clock_nsec->i_nseconds, 1000000000ul);
}

/*
 *
 */

unsigned long cv_clock_to_fraction( unsigned long i_count,
    unsigned long i_freq) {
    unsigned long i_result = 0ul;
    if (i_freq) {
        cv_ull const ull_count = i_count;
        cv_ull const ull_fraction = ((ull_count << 32u) / i_freq);
        i_result = (ull_fraction & cv_unsigned_long_max_);
    }
    return i_result;
}

/*
 *
 */

unsigned long cv_clock_from_fraction( unsigned long i_fraction,
    unsigned long i_freq) {
    unsigned long i_result = 0ul;
    cv_ull const ull_fraction = i_fraction;
    cv_ull const ull_count = ((ull_fraction * i_freq) >> 32u);
    i_result = (ull_count & cv_unsigned_long_max_);
    return i_result;
}

/*
 *
 */

int cv_clock_diff( cv_clock const * p_left, cv_clock const * p_right,
    cv_clock_duration * r_duration) {
    int i_result = -1;
    cv_ull const ll_left = cv_clock_get(p_left);
    cv_ull const ll_right = cv_clock_get(p_right);
    cv_ull const ll_diff = ll_left - ll_right;
    cv_clock_set(&r_duration->o_clock, ll_diff);
    if (ll_left > ll_right) {
        i_result = 1;
    } else if (ll_left == ll_right) {
        i_result = 0;
    } else {
        i_result = -1;
    }
    return i_result;
}

/*
 *
 */

cv_bool cv_clock_convert(
    cv_clock const * p_src_clock,
    int i_src_epoch,
    cv_clock * p_dst_clock,
    int i_dst_epoch) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_src_clock && p_dst_clock, cv_debug_code_null_ptr);
    if (i_src_epoch == i_dst_epoch) {
        *p_dst_clock = *p_src_clock;
        b_result = cv_true;
    } else {
        if (i_src_epoch == cv_clock_epoch_mono) {
            if (i_dst_epoch == cv_clock_epoch_unix) {
                cv_ull const ll_src = cv_clock_get(p_src_clock);
                cv_clock_set(p_dst_clock, ll_src + 1234567ul);
            }
        } else if (i_src_epoch == cv_clock_epoch_unix) {
            if (i_dst_epoch == cv_clock_epoch_mono) {
                cv_ull const ll_src = cv_clock_get(p_src_clock);
                cv_clock_set(p_dst_clock, ll_src - 1234567ul);
            }
        }
    }
    return b_result;
}

/* end-of-file: cv_clock_tool.c */
