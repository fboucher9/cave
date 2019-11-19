/* See LICENSE for license details */

#include <cv_heap_large.h>

#include <cv_heap_node.h>

#include <cv_heap_node_ptr.h>

#include <cv_mutex_impl.h>

#include <cv_mutex.h>

#include <cv_node_it.h>

#include <cv_sizeof.h>

#include <cv_unused.h>

#include <stdlib.h>

static char g_heap_large_loaded = 0;

static cv_mutex g_heap_large_mutex = cv_mutex_initializer_;

static cv_list g_heap_large_used_list = cv_list_initializer_;

static cv_list g_heap_large_free_list = cv_list_initializer_;

char cv_heap_large_load(void)
{
    char b_result = 0;
    if (!g_heap_large_loaded)
    {
        if (cv_list_init(&g_heap_large_used_list))
        {
            if (cv_list_init(&g_heap_large_free_list))
            {
                g_heap_large_loaded = 1;
                b_result = 1;
            }
        }
    }
    return b_result;
}

void cv_heap_large_unload(void)
{
    if (g_heap_large_loaded)
    {
        /* Detect leaks */
        /* Free all items ... */
        cv_list_cleanup(&g_heap_large_used_list);
        cv_list_cleanup(&g_heap_large_free_list);
        g_heap_large_loaded = 0;
    }
}

static long cv_heap_large_align(
    long i_len)
{
    long const i_total_len = i_len + cv_sizeof_(cv_heap_node);
    long const i_remainder = (i_total_len % 4096);
    long const i_aligned_len = i_remainder ?
        i_total_len + 4096 - i_remainder : i_total_len;
    return i_aligned_len;
}

static cv_heap_node * cv_heap_large_find_existing(
    long i_aligned_len)
{
    cv_heap_node_ptr o_heap_ptr = cv_heap_node_ptr_null_;
    cv_node_it o_free_it = cv_node_it_initializer_;
    if (cv_node_it_init(&o_free_it, &g_heap_large_free_list))
    {
        char b_found_existing = 0;
        while (!b_found_existing &&
            cv_node_it_next(&o_free_it, &o_heap_ptr.o_node_ptr))
        {
            if (i_aligned_len == cv_heap_large_align(
                    o_heap_ptr.p_heap_node->i_len))
            {
                b_found_existing = 1;
            }
        }
        cv_node_it_cleanup(&o_free_it);
    }
    return o_heap_ptr.p_heap_node;
}

static void * cv_heap_large_alloc_cb(
    long i_len)
{
    void * p_result = cv_null_;

    if (i_len > 0)
    {
        long const i_aligned_len = cv_heap_large_align(i_len);
        cv_heap_node_ptr o_heap_ptr = cv_heap_node_ptr_null_;
        /* Look for free node */
        o_heap_ptr.p_heap_node = cv_heap_large_find_existing(
            i_aligned_len);
        if (o_heap_ptr.p_heap_node)
        {
            /* Detach from free list */
            cv_node_join( o_heap_ptr.o_node_ptr.p_node,
                o_heap_ptr.o_node_ptr.p_node);
            /* See actual length */
            o_heap_ptr.p_heap_node->i_len = i_len;
        }
        else
        {
            size_t const i_malloc_len = cv_cast_(size_t, i_aligned_len);
            o_heap_ptr.p_void = malloc(i_malloc_len);
            if (o_heap_ptr.p_void)
            {
                cv_heap_node_init( o_heap_ptr.p_heap_node, i_len);
            }
        }
        if (o_heap_ptr.p_void)
        {
            /* Attach to used list */
            cv_node_join( o_heap_ptr.o_node_ptr.p_node,
                & g_heap_large_used_list.o_node);
            p_result = cv_heap_node_to_payload(o_heap_ptr.p_heap_node);
        }
    }
    return p_result;
}

static void cv_heap_large_free_cb(
    void * p_buf)
{
    if (p_buf)
    {
        cv_heap_node_ptr o_heap_ptr = cv_heap_node_ptr_null_;
        o_heap_ptr.p_heap_node = cv_heap_node_from_payload(p_buf);
        /* Detach from used list */
        cv_node_join( o_heap_ptr.o_node_ptr.p_node,
            o_heap_ptr.o_node_ptr.p_node);
        /* Attach to free list */
        cv_node_join( o_heap_ptr.o_node_ptr.p_node,
            & g_heap_large_free_list.o_node);
    }
}

void * cv_heap_large_alloc(
    long i_len)
{
    void * p_result = cv_null_;
    if (g_heap_large_loaded && (i_len > 4096))
    {
        cv_mutex_lock(&g_heap_large_mutex);
        p_result = cv_heap_large_alloc_cb(i_len);
        cv_mutex_unlock(&g_heap_large_mutex);
    }
    return p_result;
}

void cv_heap_large_free(
    void * p_buf)
{
    if (g_heap_large_loaded && p_buf)
    {
        cv_mutex_lock(&g_heap_large_mutex);
        cv_heap_large_free_cb(p_buf);
        cv_mutex_unlock(&g_heap_large_mutex);
    }
}

