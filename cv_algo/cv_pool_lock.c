/* See LICENSE for license details */

/*
 *  Module: cv_pool_lock.c
 *
 *  Description: Thread-safe version of cv_pool.
 */

#include <cv_algo/cv_pool_lock.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_pool_lock");

/*
 *
 */

cv_bool cv_pool_lock_init(
    cv_pool_lock * p_this,
    cv_pool_desc const * p_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    if (cv_mutex_init(&p_this->o_mutex)) {
        cv_pool_init(&p_this->o_pool, p_desc);
        b_result = cv_true;
    } else {
        cv_debug_destruct_(g_class, p_this);
    }
    return b_result;
}

/*
 *
 */

void cv_pool_lock_cleanup(
    cv_pool_lock * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_pool_cleanup(&p_this->o_pool);
    cv_mutex_cleanup(&p_this->o_mutex);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

void * cv_pool_lock_alloc(
    cv_pool_lock * p_this) {
    void * p_result = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_mutex_lock(&p_this->o_mutex);
    p_result = cv_pool_alloc(&p_this->o_pool);
    cv_mutex_unlock(&p_this->o_mutex);
    return p_result;
}

/*
 *
 */

void cv_pool_lock_free(
    cv_pool_lock * p_this,
    void * p_buffer) {
    cv_debug_assert_(p_this && p_buffer, cv_debug_code_null_ptr);
    cv_mutex_lock(&p_this->o_mutex);
    cv_pool_free(&p_this->o_pool, p_buffer);
    cv_mutex_unlock(&p_this->o_mutex);
}

/* end-of-file: cv_pool_lock.c */
