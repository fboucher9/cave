/* See LICENSE for license details */

#include <cv_heap.h>

#include <cv_heap_plugin.h>

#include <cv_heap_small.h>

#include <cv_heap_large.h>

#include <cv_heap_node.h>

#include <cv_heap_node_ptr.h>

#include <cv_null.h>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

static char g_heap_loaded = 0;

static long g_heap_count = 0;

char cv_heap_load(void)
{
    char b_result = 0;
    if (!g_heap_loaded)
    {
        if (cv_heap_small_load())
        {
            if (cv_heap_large_load())
            {
                g_heap_loaded = 1;
                b_result = 1;
            }
        }
    }
    return b_result;
}

void cv_heap_unload(void)
{
    if (g_heap_loaded)
    {
        printf("*** %ld leaks ***\n", g_heap_count);
        cv_heap_large_unload();
        cv_heap_small_unload();
        g_heap_loaded = 0;
    }
}

void * cv_heap_alloc(
    long i_buffer_length)
{
    void * p_buffer = cv_null_;

    if (i_buffer_length)
    {
        if (i_buffer_length <= 4096)
        {
            p_buffer = cv_heap_small_alloc(i_buffer_length);
        }
        else
        {
            p_buffer = cv_heap_large_alloc(i_buffer_length);
        }

        if (p_buffer)
        {
            g_heap_count ++;
        }
    }
    return p_buffer;
}

void cv_heap_free(
    void * p_buffer)
{
    if (
        p_buffer)
    {
        cv_heap_node const * const p_heap_node =
            cv_heap_node_from_payload(p_buffer);

        long const i_buffer_length = p_heap_node->i_len;

        if (i_buffer_length <= 4096)
        {
            cv_heap_small_free(p_buffer);
        }
        else
        {
            cv_heap_large_free(p_buffer);
        }

        g_heap_count --;
    }
    else
    {
    }
}

