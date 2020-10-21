/* See LICENSE for license details */

#include <cv_clock/cv_clock_mono_it.h>
#include <cv_clock/cv_clock_duration.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_clock_mono_it", sizeof(cv_clock_mono_it));

/*
 *
 */

void cv_clock_mono_it_init( cv_clock_mono_it * p_this,
    cv_clock_mono const * p_target) {
    cv_debug_assert_(p_this && p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    p_this->o_target = *(p_target);
}

/*
 *
 */

void cv_clock_mono_it_cleanup( cv_clock_mono_it * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_bool cv_clock_mono_it_next( cv_clock_mono_it * p_this,
    cv_clock_duration const * p_max_sleep) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_max_sleep, cv_debug_code_null_ptr);
    {
        cv_clock_mono o_now;
        cv_clock_mono_init(&o_now);
        if (cv_clock_mono_read(&o_now)) {
            cv_clock_duration o_duration;
            cv_clock_duration_init(&o_duration);
            if (0 <= cv_clock_mono_diff(&p_this->o_target,
                    &o_now, &o_duration)) {
                cv_clock_duration o_min_sleep;
                cv_clock_duration_init(&o_min_sleep);
                if (cv_clock_duration_min(&o_duration, p_max_sleep,
                        &o_min_sleep)) {
                    /* Sleep for min duration */
                    if (cv_clock_duration_until(&o_min_sleep)) {
                        /* Verify if reached end */
                        if (cv_clock_mono_read(&o_now)) {
                            if (0 <= cv_clock_mono_diff(&p_this->o_target,
                                    &o_now, &o_duration)) {
                                b_result = cv_true;
                            }
                        }
                    }
                }
                cv_clock_duration_cleanup(&o_min_sleep);
            }
            cv_clock_duration_cleanup(&o_duration);
        }
        cv_clock_mono_cleanup(&o_now);
    }
    return b_result;
}

/* end-of-file: cv_clock_mono_it.c */
