/* See LICENSE for license details */

#include <cv_heap_primary.h>

#include <cv_null.h>

#include <cv_mutex.h>

#include <cv_mutex_mgr.h>

#include <cv_list.h>

#include <cv_node.h>

#include <cv_node_it.h>

#if defined cv_have_libc_
#include <stdlib.h>
#endif /* #if defined cv_have_libc_ */

static cv_list g_heap_sections = cv_list_initializer_;

static char * g_heap_primary_cur = cv_null_;

static char * g_heap_primary_end = cv_null_;

static long g_heap_primary_max = ((1024L * 1024L) - 256L);

char cv_heap_primary_load(void)
{
    char b_result = 0;

    if (cv_list_init(&g_heap_sections))
    {
        b_result = 1;
    }

    return b_result;
}

void cv_heap_primary_unload(void)
{
    /* Free list of sections */
    {
        cv_node_it o_node_it = cv_node_it_initializer_;
        if (cv_node_it_init(&o_node_it, &g_heap_sections))
        {
            cv_node_ptr o_node_ptr = cv_node_ptr_null_;
            while (cv_node_it_first(&o_node_it, &o_node_ptr))
            {
                /* Detach from list */
                cv_node_cleanup(
                    o_node_ptr.p_node);
                /* Free memory */
#if defined cv_have_libc_
                free(o_node_ptr.p_void);
#endif /* #if defined cv_have_libc_ */
            }
            cv_node_it_cleanup(&o_node_it);
        }
    }
    cv_list_cleanup(&g_heap_sections);
}

static void cv_heap_primary_lock(void)
{
    cv_mutex_lock(&cv_heap_primary_mutex);
}

static void cv_heap_primary_unlock(void)
{
    cv_mutex_unlock(&cv_heap_primary_mutex);
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
            void * p_new_segment = cv_null_;
#if defined cv_have_libc_
            size_t const i_malloc_len = cv_cast_(size_t, g_heap_primary_max);
            p_new_segment = malloc(i_malloc_len);
#else /* #if defined cv_have_libc_ */
            p_new_segment = cv_null_;
#endif /* #if defined cv_have_libc_ */
            if (p_new_segment)
            {
                cv_node_ptr o_node_ptr = cv_node_ptr_null_;

                o_node_ptr.p_void = p_new_segment;

                cv_node_init(
                    o_node_ptr.p_node);

                cv_node_join(
                    o_node_ptr.p_node,
                    &g_heap_sections.o_node);

                o_node_ptr.p_node ++;

                g_heap_primary_cur = cv_cast_(char *, o_node_ptr.p_void);

                g_heap_primary_end = g_heap_primary_cur + g_heap_primary_max -
                    sizeof(cv_node);
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
