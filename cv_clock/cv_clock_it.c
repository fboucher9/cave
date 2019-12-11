/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock_it.h>
#include <cv_misc/cv_unused.h>
#include <cv_debug.h>
#include <cv_clock/cv_clock_duration.h>

/*
 *
 */

void cv_clock_it_init( cv_clock_it * p_this,
    cv_clock const * p_target, int i_epoch) {
    cv_debug_assert_(p_this && p_target, cv_debug_code_null_ptr);
    cv_debug_construct_(p_this);
    p_this->o_target = *p_target;
    p_this->i_epoch = i_epoch;
}

/*
 *
 */

void cv_clock_it_cleanup( cv_clock_it * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_destruct_(p_this);
}

/*
 *
 */

cv_bool cv_clock_it_next( cv_clock_it * p_this,
    cv_clock_duration const * p_max_sleep) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_max_sleep, cv_debug_code_null_ptr);
    /* Calculate duration from now to target */
    {
        cv_clock o_now = cv_clock_initializer_;
        cv_clock_init(&o_now);
        if (cv_clock_read(&o_now, p_this->i_epoch)) {
            cv_clock_duration o_duration = cv_clock_duration_initializer_;
            cv_clock_duration_init(&o_duration);
            if (0 <= cv_clock_diff(&p_this->o_target, &o_now, &o_duration)) {
                cv_clock_duration o_min_sleep =
                    cv_clock_duration_initializer_;
                cv_clock_duration_init(&o_min_sleep);
                if (cv_clock_duration_min(&o_duration, p_max_sleep,
                        &o_min_sleep)) {
                    /* Sleep for min duration */
                    if (cv_clock_duration_until(&o_min_sleep)) {
                        /* Verify if reached end */
                        if (cv_clock_read(&o_now, p_this->i_epoch)) {
                            if (0 <= cv_clock_diff(&p_this->o_target, &o_now,
                                    &o_duration)) {
                                b_result = cv_true;
                            }
                        }
                    }
                }
                cv_clock_duration_cleanup(&o_min_sleep);
            }
            cv_clock_duration_cleanup(&o_duration);
        }
        cv_clock_cleanup(&o_now);
    }
    return b_result;
}

/* end-of-file: cv_clock_it.c */
