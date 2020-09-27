/* See LICENSE for license details */

/*
 *
 */

#include <cv_thread/cv_once.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(cv_once_class, "cv_once");

/*
 *
 */

void cv_once_init(struct cv_once * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(cv_once_class, p_this);
    cv_mutex_init(&p_this->o_mutex);
    p_this->o_done.b_done = cv_false;
}

/*
 *
 */

void cv_once_cleanup(struct cv_once * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_mutex_cleanup(&p_this->o_mutex);
    cv_debug_destruct_(cv_once_class, p_this);
}

/*
 *
 */

cv_bool cv_once_lock(struct cv_once * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->o_done.b_done) {
    } else {
        cv_mutex_lock(&p_this->o_mutex);
        if (p_this->o_done.b_done) {
            cv_mutex_unlock(&p_this->o_mutex);
        } else {
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

void cv_once_unlock(struct cv_once * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_this->o_done.b_done = cv_true;
    cv_mutex_unlock(&p_this->o_mutex);
}

/* end-of-file: cv_once.c */
