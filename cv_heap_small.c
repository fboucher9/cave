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

typedef char cv_verify_heap_small_align [
    (cv_heap_small_align_ * cv_heap_small_count_) == cv_heap_small_max_len_
    ? 1 : -1 ];

static cv_bool g_heap_small_loaded = cv_false;

static cv_heap_pool * g_heap_small_pool[cv_heap_small_count_];

cv_bool cv_heap_small_load(void)
{
    cv_bool b_result = cv_false;
    if (!g_heap_small_loaded)
    {
        long i_pool_index = 0;
        b_result = cv_true;
        while (b_result && (i_pool_index < cv_heap_small_count_))
        {
            g_heap_small_pool[i_pool_index] = cv_heap_pool_load(
                (i_pool_index + 1) * cv_heap_small_align_);
            if (g_heap_small_pool[i_pool_index])
            {
                i_pool_index ++;
            }
            else
            {
                while (i_pool_index)
                {
                    i_pool_index --;
                    cv_heap_pool_unload(g_heap_small_pool[i_pool_index]);
                }
                b_result = cv_false;
            }
        }
        if (b_result)
        {
            g_heap_small_loaded = cv_true;
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
            cv_heap_pool_unload(g_heap_small_pool[i_pool_index]);
            i_pool_index ++;
        }
        g_heap_small_loaded = cv_false;
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
        long const i_pool_index = (i_aligned_len - 1) / cv_heap_small_align_;

        if ((i_pool_index >= 0) && (i_pool_index < cv_heap_small_count_))
        {
            cv_heap_pool * const p_heap_pool =
                g_heap_small_pool[i_pool_index];

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

        long const i_pool_index = (i_len - 1) / cv_heap_small_align_;

        if ((i_pool_index >= 0) && (i_pool_index < cv_heap_small_count_))
        {
            cv_heap_pool * const p_heap_pool =
                g_heap_small_pool[i_pool_index];

            cv_heap_pool_free(p_heap_pool, p_buf);
        }
    }
}

