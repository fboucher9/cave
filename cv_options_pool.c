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

static char g_options_pool_loaded = 0;

static cv_heap_pool * g_options_pool = cv_null_;

char cv_options_pool_load(void)
{
    char b_result = 0;
    if (!g_options_pool_loaded)
    {
        g_options_pool = cv_heap_pool_load(cv_sizeof_(cv_options_node));
        if (g_options_pool)
        {
            g_options_pool_loaded = 1;
            b_result = 1;
        }
    }
    return b_result;
}

void cv_options_pool_unload(void)
{
    if (g_options_pool_loaded)
    {
        if (g_options_pool)
        {
            cv_heap_pool_unload(g_options_pool);
            g_options_pool = cv_null_;
        }
        g_options_pool_loaded = 0;
    }
}

cv_options_node * cv_options_pool_alloc(void)
{
    cv_options_node_ptr o_placement = cv_options_node_ptr_null_;
    if (g_options_pool_loaded && g_options_pool)
    {
        o_placement.o_node_ptr.p_void = cv_heap_pool_alloc(g_options_pool,
            cv_sizeof_(cv_options_node));
    }
    return o_placement.p_options_node;
}

void cv_options_pool_free(
    cv_options_node * p_options_node)
{
    if (p_options_node && g_options_pool_loaded && g_options_pool)
    {
        cv_options_node_ptr o_placement = cv_options_node_ptr_null_;
        o_placement.p_options_node = p_options_node;
        cv_heap_pool_free(g_options_pool, o_placement.o_node_ptr.p_void);
    }
}
