/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock_mono.h>
#include <cv_debug.h>
#include <cv_misc/cv_sizeof.h>

/*
 *
 */

void cv_clock_mono_init(
    cv_clock_mono * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(p_this);
    cv_clock_init(&p_this->o_clock);
}

/*
 *
 */

void cv_clock_mono_cleanup(
    cv_clock_mono * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_clock_cleanup(&p_this->o_clock);
    cv_debug_destruct_(p_this);
}

/*
 *
 */

cv_bool cv_clock_mono_read(
    cv_clock_mono * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    if (cv_clock_read(&p_this->o_clock, cv_clock_epoch_mono)) {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_clock_mono_until(
    cv_clock_mono const * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    if (cv_clock_until(&p_this->o_clock, cv_clock_epoch_mono)) {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_clock_mono_info(
    cv_clock_mono const * p_this,
    cv_clock_info * r_info) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_info, cv_debug_code_null_ptr);
    if (cv_clock_get_info(&p_this->o_clock, cv_clock_epoch_mono, r_info)) {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

int cv_clock_mono_diff( cv_clock_mono const * p_left,
    cv_clock_mono const * p_right, cv_clock_duration * r_duration) {
    cv_debug_assert_(p_left && p_right && r_duration, cv_debug_code_null_ptr);
    return cv_clock_diff(&p_left->o_clock, &p_right->o_clock, r_duration);
}

/* end-of-file: cv_clock_mono.c */
