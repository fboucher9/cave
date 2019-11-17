/* See LICENSE for license details */

#include <cv_mutex.h>

#include <cv_mutex_impl.h>

#include <cv_null.h>

#include <cv_heap.h>

char cv_mutex_init(
    cv_mutex * p_this)
{
    char b_result = 0;
    if (p_this)
    {
        int const i_pthread_result = pthread_mutex_init(&p_this->o_private,
            cv_null_);
        if (0 == i_pthread_result)
        {
            b_result = 1;
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
        int const i_pthread_result = pthread_mutex_destroy(&p_this->o_private);
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

    p_this = cv_new_(cv_mutex);

    if (p_this)
    {
        if (cv_mutex_init(p_this))
        {
        }
        else
        {
            cv_delete_(p_this);
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
        cv_delete_(p_this);
    }
}

void cv_mutex_lock(
    cv_mutex * p_this)
{
    if (p_this)
    {
        int const i_pthread_result = pthread_mutex_lock(
            &p_this->o_private);
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
        int const i_pthread_result = pthread_mutex_unlock(
            &p_this->o_private);
        if (0 == i_pthread_result)
        {
        }
        else
        {
        }
    }
}

