/* See LICENSE for license details */

#include <cv_mutex_mgr.h>

#include <cv_mutex_impl.h>

#include <cv_mutex.h>

#include <cv_mutex_ptr.h>

#include <cv_heap_primary.h>

cv_mutex cv_heap_primary_mutex = cv_mutex_initializer_;

cv_mutex cv_heap_large_mutex = cv_mutex_initializer_;

cv_mutex * cv_mutex_mgr_acquire(void)
{
    cv_mutex_ptr o_mutex_ptr = cv_ptr_null_;
    o_mutex_ptr.p_void = cv_heap_primary_alloc( cv_mutex_sizeof());
    if (o_mutex_ptr.p_void)
    {
        if (cv_mutex_init(o_mutex_ptr.p_mutex))
        {
        }
        else
        {
            /* leak? */
            o_mutex_ptr.p_void = cv_null_;
        }
    }
    return o_mutex_ptr.p_mutex;
}

void cv_mutex_mgr_release(
    cv_mutex * p_this)
{
    if (p_this)
    {
        cv_mutex_cleanup(p_this);
        /* leak? */
    }
}

