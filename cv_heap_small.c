/* See LICENSE for license details */

#include <cv_heap_small.h>

#include <cv_heap_pool.h>

#include <cv_heap_node_ptr.h>

#include <cv_heap_node.h>

#include <cv_heap_primary.h>

#include <cv_null.h>

#include <cv_sizeof.h>

#define cv_heap_small_align_ (16)

#define cv_heap_small_count_ (256)

#define cv_heap_small_max_len_ (4096)

typedef char cv_verify_heap_small_align [
    (cv_heap_small_align_ * cv_heap_small_count_) == cv_heap_small_max_len_
    ? 1 : -1 ];

static char g_heap_small_loaded = 0;

static cv_heap_pool * g_heap_small_pool = cv_null_;

char cv_heap_small_load(void)
{
    char b_result = 0;
    if (!g_heap_small_loaded)
    {
        long const i_placement_len =
            cv_sizeof_(cv_heap_pool) * cv_heap_small_count_;

        void * const p_placement =
            cv_heap_primary_alloc(i_placement_len);

        if (p_placement)
        {
            long i_pool_index = 0;
            g_heap_small_pool = cv_cast_(cv_heap_pool *, p_placement);
            b_result = 1;
            while (b_result && (i_pool_index < cv_heap_small_count_))
            {
                b_result = cv_heap_pool_init(g_heap_small_pool + i_pool_index,
                    (i_pool_index + 1) * cv_heap_small_align_);
                if (b_result)
                {
                    i_pool_index ++;
                }
                else
                {
                    while (i_pool_index)
                    {
                        i_pool_index --;
                        cv_heap_pool_cleanup(g_heap_small_pool + i_pool_index);
                    }
                }
            }
            if (b_result)
            {
                g_heap_small_loaded = 1;
            }
        }
    }
    return b_result;
}

void cv_heap_small_unload(void)
{
    if (g_heap_small_loaded)
    {
        long i_pool_index = 0;
        while (i_pool_index < cv_heap_small_count_)
        {
            cv_heap_pool_cleanup(g_heap_small_pool + i_pool_index);
            i_pool_index ++;
        }
        g_heap_small_loaded = 0;
    }
}

void * cv_heap_small_alloc(
    long i_len)
{
    void * p_result = cv_null_;

    if (g_heap_small_loaded && (i_len > 0))
    {
        /* Align len to multiple */
        long const i_remainder = i_len % cv_heap_small_align_;

        long const i_aligned_len = i_remainder ?
            i_len + cv_heap_small_align_ - i_remainder : i_len;

        /* Locate pool */
        int const i_pool_index = cv_cast_(int,
            (i_aligned_len - 1) / cv_heap_small_align_);

        if ((i_pool_index >= 0) && (i_pool_index < cv_heap_small_count_))
        {
            cv_heap_pool * const p_heap_pool =
                g_heap_small_pool + i_pool_index;

            p_result = cv_heap_pool_alloc(p_heap_pool, i_len);
        }
    }

    return p_result;
}

void cv_heap_small_free(
    void * p_buf)
{
    if (g_heap_small_loaded && p_buf)
    {
        cv_heap_node const * p_heap_node =
            cv_heap_node_from_payload(p_buf);

        long const i_len = p_heap_node->i_len;

        long const i_pool_index = cv_cast_(int,
            (i_len - 1) / cv_heap_small_align_);

        if ((i_pool_index >= 0) && (i_pool_index < cv_heap_small_count_))
        {
            cv_heap_pool * const p_heap_pool =
                g_heap_small_pool + i_pool_index;

            cv_heap_pool_free(p_heap_pool, p_buf);
        }
    }
}

