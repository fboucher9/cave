/* See LICENSE for license details */

/*
 *
 */

#include <cv_thread/cv_mutex.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_mutex", sizeof(cv_mutex));

/*
 *
 */

cv_bool cv_mutex_init(
    cv_mutex * p_this)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    {
        int i_pthread_result = 0;
        i_pthread_result = cv_mutex_impl_init(p_this);
        if (0 == i_pthread_result) {
            b_result = cv_true;
        }
    }
    if (!b_result) {
        cv_debug_destruct_(g_class, p_this);
    }
    return b_result;
}

/*
 *
 */

void cv_mutex_cleanup(
    cv_mutex * p_this)
{
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    {
        int i_pthread_result = 0;
        i_pthread_result = cv_mutex_impl_cleanup(p_this);
        if (0 == i_pthread_result) {
        }
    }
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

void cv_mutex_lock(
    cv_mutex * p_this)
{
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    {
        int i_pthread_result = 0;
        i_pthread_result = cv_mutex_impl_lock(p_this);
        if (0 == i_pthread_result) {
        }
    }
}

/*
 *
 */

void cv_mutex_unlock(
    cv_mutex * p_this)
{
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    {
        int i_pthread_result = 0;
        i_pthread_result = cv_mutex_impl_unlock(p_this);
        if (0 == i_pthread_result) {
        }
    }
}

/* end-of-file: cv_mutex.c */
