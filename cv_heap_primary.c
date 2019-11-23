/* See LICENSE for license details */

#include <cv_heap_primary.h>

#include <cv_null.h>

#include <cv_mutex.h>

#include <cv_mutex_mgr.h>

#include <cv_list.h>

#include <cv_node.h>

#include <cv_node_it.h>

#include <cv_runtime.h>

typedef union cv_heap_section_ptr cv_heap_section_ptr;

union cv_heap_section_ptr
{
    cv_node_ptr o_node_ptr;
    char * p_char;
};

#define cv_heap_section_ptr_null_ { cv_node_ptr_null_ }

static cv_list g_heap_sections = cv_list_initializer_;

static char * g_heap_primary_cur = cv_null_;

static char * g_heap_primary_end = cv_null_;

static long g_heap_primary_max = ((1024L * 1024L) - 256L);

cv_bool cv_heap_primary_load(void)
{
    cv_bool b_result = cv_false_;

    if (cv_list_init(&g_heap_sections))
    {
        b_result = cv_true_;
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
                cv_runtime_free(o_node_ptr.p_void);
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

static void cv_heap_primary_grow(void)
{
    cv_heap_section_ptr o_section_ptr = cv_heap_section_ptr_null_;
    o_section_ptr.o_node_ptr.p_void = cv_runtime_malloc(g_heap_primary_max);
    if (o_section_ptr.o_node_ptr.p_void)
    {
        cv_node_init(
            o_section_ptr.o_node_ptr.p_node);

        cv_node_join(
            o_section_ptr.o_node_ptr.p_node,
            &g_heap_sections.o_node);

        o_section_ptr.o_node_ptr.p_node ++;

        g_heap_primary_cur = o_section_ptr.p_char;

        g_heap_primary_end = g_heap_primary_cur + g_heap_primary_max -
            sizeof(cv_node);
    }
}

static void * cv_heap_primary_alloc_cb(
    long i_count)
{
    void * p_buffer = cv_null_;

    long const i_alignment = 8;

    long const i_remainder = i_count % i_alignment;

    long const i_aligned_count = i_remainder ?
        i_count + i_alignment - i_remainder : i_count;

    if ((g_heap_primary_cur + i_aligned_count) > g_heap_primary_end)
    {
        cv_heap_primary_grow();
    }

    if ((g_heap_primary_cur + i_aligned_count) <= g_heap_primary_end)
    {
        p_buffer = g_heap_primary_cur;

        g_heap_primary_cur += i_aligned_count;
    }

    return p_buffer;
}

void * cv_heap_primary_alloc(
    long i_count)
{
    void * p_buffer = cv_null_;

    if ((i_count > 0) && (i_count <= g_heap_primary_max))
    {
        cv_heap_primary_lock();

        p_buffer = cv_heap_primary_alloc_cb(i_count);

        cv_heap_primary_unlock();
    }

    return p_buffer;
}
