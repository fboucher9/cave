/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock_counter.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_convert.h>

cv_debug_decl_(g_class, "cv_clock_counter", sizeof(cv_clock_counter));

/*
 *
 */

void cv_clock_counter_init( cv_clock_counter * p_this ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_clock_init(&p_this->o_clock);
}

/*
 *
 */

void cv_clock_counter_cleanup( cv_clock_counter * p_this ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_clock_cleanup(&p_this->o_clock);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_ull cv_clock_counter_get( cv_clock_counter const * p_this ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    return cv_clock_get(&p_this->o_clock);
}

/*
 *
 */

void cv_clock_counter_set( cv_clock_counter * p_this, cv_ull ll_value ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_clock_set(&p_this->o_clock, ll_value);
}

/*
 *
 */

void cv_clock_counter_inc( cv_clock_counter * p_this ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_clock_counter_add(p_this, 1);
}

/*
 *
 */

void cv_clock_counter_dec( cv_clock_counter * p_this ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_clock_counter_sub(p_this, 1);
}

/*
 *
 */

void cv_clock_counter_add( cv_clock_counter * p_this,
    unsigned long i_value ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    {
        cv_ull const ll_count = cv_clock_counter_get(p_this);
        cv_clock_counter_set(p_this, ll_count + i_value);
    }
}

/*
 *
 */

void cv_clock_counter_sub( cv_clock_counter * p_this,
    unsigned long i_value ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    {
        cv_ull const ll_count = cv_clock_counter_get(p_this);
        cv_clock_counter_set(p_this, ll_count - i_value);
    }
}

/* end-of-file: cv_clock_counter.c */
