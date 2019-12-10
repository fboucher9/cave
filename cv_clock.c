/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock.h>
#include <cv_debug.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_misc/cv_cast.h>
#include <cv_misc/cv_types.h>
#include <cv_misc/cv_limits.h>
#include <cv_misc/cv_convert.h>
#include <cv_misc/cv_unused.h>

#if defined cv_have_libc_
#include <time.h>
#endif /* #if defined cv_have_libc_ */

#if defined cv_linux_
#include <unistd.h>
#endif /* #if defined cv_linux_ */

/*
 *
 */

void cv_clock_init(
    cv_clock * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    p_this->i_seconds = 0;
    p_this->i_fraction = 0;
}

/*
 *
 */

void cv_clock_cleanup(
    cv_clock * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    /* ... */
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

/*
 *
 */

#if defined cv_linux_
static void cv_clock_from_linux_timespec(
    cv_clock * p_this,
    struct timespec const * p_linux_timespec) {
    cv_ull const ull_sec = cv_convert_ll2u_(p_linux_timespec->tv_sec);
    cv_ull const ull_nsec = cv_convert_ll2u_(p_linux_timespec->tv_nsec);
    p_this->i_seconds = ull_sec & cv_unsigned_long_max_;
    p_this->i_fraction = ((ull_nsec << 32u) / 1000000000UL) &
        cv_unsigned_long_max_;
}
#endif /* #if defined cv_linux_ */

/*
 *
 */

#if defined cv_linux_
static cv_bool cv_clock_read_linux(
    cv_clock * p_this,
    cv_clock_epoch e_epoch) {
    cv_bool b_result = cv_false;
    if (cv_clock_epoch_mono == e_epoch) {
        struct timespec o_linux_timespec;
        int const i_linux_result = clock_gettime(
            CLOCK_MONOTONIC, &o_linux_timespec);
        if (0 == i_linux_result) {
            cv_clock_from_linux_timespec(p_this, &o_linux_timespec);
            b_result = cv_true;
        } else {
            cv_debug_msg_(cv_debug_code_error);
        }
    } else {
        cv_debug_msg_(cv_debug_code_not_implemented);
    }
    return b_result;
}
#endif /* #if defined cv_linux_ */

/*
 *
 */

cv_bool cv_clock_read(
    cv_clock * p_this,
    cv_clock_epoch e_epoch) {
    cv_bool b_result = cv_false;
#if defined cv_linux_
    b_result = cv_clock_read_linux(p_this, e_epoch);
#else /* #if defined cv_linux_ */
    cv_unused_(p_this);
    cv_unused_(e_epoch);
    cv_debug_msg_(cv_debug_code_not_implemented);
#endif /* #if defined cv_linux_ */
    return b_result;
}

/*
 *
 */

cv_bool cv_clock_until(
    cv_clock const * p_this,
    cv_clock_epoch e_epoch) {
    cv_bool b_result = cv_false;
    cv_unused_(p_this);
    cv_unused_(e_epoch);
    return b_result;
}

/*
 *
 */

cv_bool cv_clock_get_info(
    cv_clock const * p_this,
    cv_clock_epoch e_epoch,
    cv_clock_info * r_info) {
    cv_bool b_result = cv_false;
    cv_unused_(p_this);
    cv_unused_(e_epoch);
    cv_unused_(r_info);
    return b_result;
}

/* end-of-file: cv_clock.c */
