/* See LICENSE for license details */

#include <cv_heap_primary.h>

#include <cv_null.h>

#include <cv_mutex.h>

#include <cv_mutex_impl.h>

#include <stdlib.h>

static char * g_heap_primary_cur = cv_null_;

static char * g_heap_primary_end = cv_null_;

static long g_heap_primary_max = ((1024L * 1024L) - 256L);

static cv_mutex g_heap_primary_lock = cv_mutex_initializer_;

static void cv_heap_primary_lock(void)
{
    cv_mutex_lock(&g_heap_primary_lock);
}

static void cv_heap_primary_unlock(void)
{
    cv_mutex_unlock(&g_heap_primary_lock);
}

void * cv_heap_primary_alloc(
    long i_count)
{
    void * p_buffer = cv_null_;

    if ((i_count > 0) && (i_count <= g_heap_primary_max))
    {
        long const i_alignment = 8;

        long const i_remainder = i_count % i_alignment;

        long const i_aligned_count = i_remainder ?
            i_count + i_alignment - i_remainder : i_count;

        cv_heap_primary_lock();

        if ((g_heap_primary_cur + i_aligned_count) > g_heap_primary_end)
        {
            size_t const i_malloc_len = cv_cast_(size_t, g_heap_primary_max);

            void * const p_new_segment = malloc(i_malloc_len);

            if (p_new_segment)
            {
                g_heap_primary_cur = cv_cast_(char *, p_new_segment);

                g_heap_primary_end = g_heap_primary_cur + g_heap_primary_max;
            }
        }

        if ((g_heap_primary_cur + i_aligned_count) <= g_heap_primary_end)
        {
            p_buffer = g_heap_primary_cur;

            g_heap_primary_cur += i_aligned_count;
        }

        cv_heap_primary_unlock();
    }

    return p_buffer;
}
