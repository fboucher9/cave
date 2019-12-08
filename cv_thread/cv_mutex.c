/* See LICENSE for license details */

/*
 *
 */

#include <cv_thread/cv_mutex.h>
#include <cv_thread/cv_mutex_plugin.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_misc/cv_null.h>
#include <cv_debug.h>

static cv_bool g_mutex_loaded = cv_false;

cv_bool cv_mutex_load(void)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(!g_mutex_loaded, cv_debug_code_already_loaded);
    g_mutex_loaded = cv_true;
    b_result = cv_true;
    return b_result;
}

void cv_mutex_unload(void)
{
    cv_debug_assert_(g_mutex_loaded, cv_debug_code_already_unloaded);
    g_mutex_loaded = cv_false;
}

cv_bool cv_mutex_init(
    cv_mutex * p_this)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(g_mutex_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    {
        int i_pthread_result = 0;
#if defined cv_have_pthread_
        i_pthread_result = pthread_mutex_init(&p_this->o_private,
            cv_null_);
#endif /* #if defined cv_have_pthread_ */
        if (0 == i_pthread_result) {
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_mutex_cleanup(
    cv_mutex * p_this)
{
    cv_debug_assert_(g_mutex_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    {
        int i_pthread_result = 0;
#if defined cv_have_pthread_
        i_pthread_result = pthread_mutex_destroy(&p_this->o_private);
#endif /* #if defined cv_have_pthread_ */
        if (0 == i_pthread_result) {
        }
    }
}

void cv_mutex_lock(
    cv_mutex * p_this)
{
    cv_debug_assert_(g_mutex_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    {
        int i_pthread_result = 0;
#if defined cv_have_pthread_
        i_pthread_result = pthread_mutex_lock(
            &p_this->o_private);
#endif /* #if defined cv_have_pthread_ */
        if (0 == i_pthread_result) {
        }
    }
}

void cv_mutex_unlock(
    cv_mutex * p_this)
{
    cv_debug_assert_(g_mutex_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    {
        int i_pthread_result = 0;
#if defined cv_have_pthread_
        i_pthread_result = pthread_mutex_unlock(
            &p_this->o_private);
#endif /* #if defined cv_have_pthread_ */
        if (0 == i_pthread_result) {
        }
    }
}

