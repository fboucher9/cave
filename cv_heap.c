/* See LICENSE for license details */

#include <cv_heap.h>

#include <cv_heap_plugin.h>

#include <cv_heap_small.h>

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
            g_heap_loaded = 1;
            b_result = 1;
        }
    }
    return b_result;
}

void cv_heap_unload(void)
{
    if (g_heap_loaded)
    {
        printf("*** %ld leaks ***\n", g_heap_count);
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
#if 0
            size_t const i_calloc_len = cv_cast_(size_t, i_buffer_length);
            p_buffer = calloc(i_calloc_len, 1);
            if (p_buffer)
            {
                g_heap_count ++;
            }
#endif
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
    if (p_buffer)
    {
        cv_heap_small_free(p_buffer);

#if 0
        free(p_buffer);
#endif

        g_heap_count --;
    }
    else
    {
    }
}

