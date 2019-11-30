/* See LICENSE for license details */

/*

Module: cv_options_pool.c

Description: Memory allocation pool for cv_options_node objects.

*/

#include <cv_options_pool.h>

#include <cv_heap_pool.h>

#include <cv_options_node.h>

#include <cv_options_node_ptr.h>

#include <cv_sizeof.h>

#include <cv_debug.h>

static cv_bool g_options_pool_loaded = cv_false;

static cv_heap_pool * g_options_pool = cv_null_;

cv_bool cv_options_pool_load(void)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(
        !g_options_pool_loaded,
        "already loaded");
    {
        g_options_pool = cv_heap_pool_load(cv_sizeof_(cv_options_node));
        if (g_options_pool)
        {
            g_options_pool_loaded = cv_true;
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_options_pool_unload(void)
{
    cv_debug_assert_(
        g_options_pool_loaded,
        "already unloaded");
    {
        if (g_options_pool)
        {
            cv_heap_pool_unload(g_options_pool);
            g_options_pool = cv_null_;
        }
        g_options_pool_loaded = cv_false;
    }
}

cv_options_node * cv_options_pool_alloc(void)
{
    cv_options_node_ptr o_placement = cv_ptr_null_;
    cv_debug_assert_(
        g_options_pool_loaded && g_options_pool,
        "not loaded");
    {
        o_placement.o_list_ptr.p_void = cv_heap_pool_alloc(g_options_pool,
            cv_sizeof_(cv_options_node));
    }
    return o_placement.p_options_node;
}

void cv_options_pool_free(
    cv_options_node * p_options_node)
{
    cv_debug_assert_(
        g_options_pool_loaded && g_options_pool,
        "not loaded");
    if (p_options_node)
    {
        cv_options_node_ptr o_placement = cv_ptr_null_;
        o_placement.p_options_node = p_options_node;
        cv_heap_pool_free(g_options_pool, o_placement.o_list_ptr.p_void);
    }
}

