/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_duration.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_clock/cv_clock_plugin.h>
#include <cv_debug.h>
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

cv_bool cv_clock_load(void) {
    cv_bool b_result = cv_false;
    b_result = cv_true;
    return b_result;
}

/*
 *
 */

void cv_clock_unload(void) {
}

/*
 *
 */

void cv_clock_init( cv_clock * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(p_this);
    p_this->i_seconds = 0;
    p_this->i_fraction = 0;
}

/*
 *
 */

void cv_clock_cleanup( cv_clock * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    /* ... */
    cv_debug_destruct_(p_this);
}

/*
 *
 */

#if defined cv_linux_
static void cv_clock_from_linux_timespec( cv_clock * p_this,
    struct timespec const * p_linux_timespec) {
    cv_ull const ull_sec = cv_convert_ll2u_(p_linux_timespec->tv_sec);
    unsigned long const ui_nsec = cv_convert_l2u_(p_linux_timespec->tv_nsec);
    p_this->i_seconds = ull_sec & cv_unsigned_long_max_;
    p_this->i_fraction = cv_clock_to_fraction(ui_nsec, 1000000000UL);
}
#endif /* #if defined cv_linux_ */

/*
 *
 */

#if defined cv_linux_
static void cv_clock_to_linux_timespec( cv_clock const * p_this,
    struct timespec * p_linux_timespec) {
    unsigned long ui_nsec = cv_clock_from_fraction(p_this->i_fraction,
        1000000000UL);
    p_linux_timespec->tv_sec = cv_convert_u2l_(p_this->i_seconds);
    p_linux_timespec->tv_nsec = cv_convert_u2l_(ui_nsec);
}
#endif /* #if defined cv_linux_ */

/*
 *
 */

#if defined cv_linux_
static cv_bool cv_clock_read_linux( cv_clock * p_this,
    int e_epoch) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
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
    } else if (cv_clock_epoch_unix == e_epoch) {
        struct timespec o_linux_timespec;
        int const i_linux_result = clock_gettime(
            CLOCK_REALTIME, &o_linux_timespec);
        if (0 == i_linux_result) {
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

cv_bool cv_clock_read( cv_clock * p_this, int e_epoch) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
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

#if defined cv_linux_
static cv_bool cv_clock_until_linux( cv_clock const * p_this,
    int e_epoch) {
    cv_bool b_result = cv_false;
    struct timespec o_linux_request;
    cv_clock_to_linux_timespec(p_this, &o_linux_request);
    if (cv_clock_epoch_mono == e_epoch) {
        int const i_linux_result = clock_nanosleep(CLOCK_MONOTONIC,
            TIMER_ABSTIME, &o_linux_request, NULL);
        if (0 <= i_linux_result) {
            b_result = cv_true;
        }
    } else if (cv_clock_epoch_unix == e_epoch) {
        int const i_linux_result = clock_nanosleep(CLOCK_REALTIME,
            TIMER_ABSTIME, &o_linux_request, NULL);
        if (0 <= i_linux_result) {
            b_result = cv_true;
        }
    } else if (cv_clock_epoch_duration == e_epoch) {
        int const i_linux_result = clock_nanosleep(CLOCK_MONOTONIC,
            0, &o_linux_request, NULL);
        if (0 <= i_linux_result) {
            b_result = cv_true;
        }
    } else {
    }
    return b_result;
}
#endif /* #if defined cv_linux_ */

/*
 *
 */

cv_bool cv_clock_until( cv_clock const * p_this, int e_epoch) {
    cv_bool b_result = cv_false;
#if defined cv_linux_
    b_result = cv_clock_until_linux(p_this, e_epoch);
#else /* #if defined cv_linux_ */
    cv_unused_(p_this);
    cv_unused_(e_epoch);
#endif /* #if defined cv_linux_ */
    return b_result;
}

/*
 *
 */

cv_bool cv_clock_query( cv_clock const * p_this,
    int e_epoch, cv_clock_info * r_info) {
    cv_bool b_result = cv_false;
    cv_unused_(p_this);
    cv_unused_(e_epoch);
    cv_unused_(r_info);
    return b_result;
}

/* end-of-file: cv_clock.c */
