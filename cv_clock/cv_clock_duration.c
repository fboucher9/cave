/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock_duration.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_limits.h>
#include <cv_misc/cv_types.h>
#include <cv_clock/cv_clock_tool.h>

cv_debug_decl_(g_class);

/*
 *
 */

static cv_ull cv_clock_duration_get( cv_clock_duration const * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    return cv_clock_get(&p_this->o_clock);
}

/*
 *
 */

static void cv_clock_duration_set( cv_clock_duration * p_this,
    cv_ull ll_value) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_clock_set(&p_this->o_clock, ll_value);
}

/*
 *
 */

void cv_clock_duration_init( cv_clock_duration * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_clock_init(&p_this->o_clock);
}

/*
 *
 */

void cv_clock_duration_cleanup( cv_clock_duration * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_clock_cleanup(&p_this->o_clock);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_bool cv_clock_duration_until( cv_clock_duration const * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    return cv_clock_until(&p_this->o_clock, cv_clock_epoch_duration);
}


/*
 *
 */

cv_bool cv_clock_duration_min( cv_clock_duration const * p_left,
    cv_clock_duration const * p_right, cv_clock_duration * r_result) {
    cv_ull const ll_left = cv_clock_duration_get(p_left);
    cv_ull const ll_right = cv_clock_duration_get(p_right);
    cv_ull const ll_result = (ll_left < ll_right) ? ll_left : ll_right;
    cv_clock_duration_set(r_result, ll_result);
    return cv_true;
}

/* end-of-file: cv_clock_duration.c */
