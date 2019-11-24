/* See LICENSE for license details */

#include <cv_mutex.h>

#include <cv_mutex_impl.h>

#include <cv_mutex_pool.h>

#include <cv_mutex_plugin.h>

#include <cv_sizeof.h>

#include <cv_null.h>

cv_bool cv_mutex_load(void)
{
    cv_bool b_result = cv_false;
    b_result = cv_mutex_pool_load();
    return b_result;
}

void cv_mutex_unload(void)
{
    cv_mutex_pool_unload();
}

long cv_mutex_sizeof(void)
{
    return cv_sizeof_(cv_mutex);
}

cv_bool cv_mutex_init(
    cv_mutex * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        int i_pthread_result = 0;
#if defined cv_have_pthread_
        i_pthread_result = pthread_mutex_init(&p_this->o_private,
            cv_null_);
#endif /* #if defined cv_have_pthread_ */
        if (0 == i_pthread_result)
        {
            b_result = cv_true;
        }
        else
        {
        }
    }
    return b_result;
}

void cv_mutex_cleanup(
    cv_mutex * p_this)
{
    if (p_this)
    {
        int i_pthread_result = 0;
#if defined cv_have_pthread_
        i_pthread_result = pthread_mutex_destroy(&p_this->o_private);
#endif /* #if defined cv_have_pthread_ */
        if (0 == i_pthread_result)
        {
        }
        else
        {
        }
    }
}

cv_mutex * cv_mutex_create(void)
{
    cv_mutex * p_this = cv_null_;

    p_this = cv_mutex_pool_alloc();

    if (p_this)
    {
        if (cv_mutex_init(p_this))
        {
        }
        else
        {
            cv_mutex_pool_free(p_this);
            p_this = cv_null_;
        }
    }

    return p_this;
}

void cv_mutex_destroy(
    cv_mutex * p_this)
{
    if (p_this)
    {
        cv_mutex_cleanup(p_this);
        cv_mutex_pool_free(p_this);
    }
}

void cv_mutex_lock(
    cv_mutex * p_this)
{
    if (p_this)
    {
        int i_pthread_result = 0;

#if defined cv_have_pthread_
        i_pthread_result = pthread_mutex_lock(
            &p_this->o_private);
#endif /* #if defined cv_have_pthread_ */

        if (0 == i_pthread_result)
        {
        }
        else
        {
        }
    }
}

void cv_mutex_unlock(
    cv_mutex * p_this)
{
    if (p_this)
    {
        int i_pthread_result = 0;

#if defined cv_have_pthread_
        pthread_mutex_unlock(
            &p_this->o_private);
#endif /* #if defined cv_have_pthread_ */

        if (0 == i_pthread_result)
        {
        }
        else
        {
        }
    }
}

