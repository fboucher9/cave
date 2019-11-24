/* See LICENSE for license details */

#include <cv_mutex_pool.h>

#include <cv_heap_pool.h>

#include <cv_mutex.h>

#include <cv_mutex_ptr.h>

#include <cv_null.h>

static cv_bool g_mutex_pool_loaded = cv_false;

static cv_heap_pool * g_mutex_pool = cv_null_;

cv_bool cv_mutex_pool_load(void)
{
    cv_bool b_result = cv_false;
    if (!g_mutex_pool_loaded)
    {
        g_mutex_pool = cv_heap_pool_load(cv_mutex_sizeof());
        if (g_mutex_pool)
        {
            g_mutex_pool_loaded = cv_true;
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_mutex_pool_unload(void)
{
    if (g_mutex_pool_loaded)
    {
        if (g_mutex_pool)
        {
            cv_heap_pool_unload( g_mutex_pool);
            g_mutex_pool = cv_null_;
        }
        g_mutex_pool_loaded = cv_false;
    }
}

cv_mutex * cv_mutex_pool_alloc(void)
{
    cv_mutex_ptr o_placement = cv_ptr_null_;
    if (g_mutex_pool_loaded && g_mutex_pool)
    {
        o_placement.p_void = cv_heap_pool_alloc(g_mutex_pool,
            cv_mutex_sizeof());
    }
    return o_placement.p_mutex;
}

void cv_mutex_pool_free(
    cv_mutex * p_mutex)
{
    if (p_mutex && g_mutex_pool_loaded && g_mutex_pool)
    {
        cv_mutex_ptr o_placement = cv_ptr_null_;
        o_placement.p_mutex = p_mutex;
        cv_heap_pool_free(g_mutex_pool, o_placement.p_void);
    }
}

