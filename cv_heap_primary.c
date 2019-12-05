/* See LICENSE for license details */

#include <cv_heap_primary.h>

#include <cv_null.h>

#include <cv_mutex.h>

#include <cv_list_root.h>

#include <cv_list_node.h>

#include <cv_list_it.h>

#include <cv_runtime.h>

#include <cv_sizeof.h>

#include <cv_heap_section.h>

static cv_heap_section_list g_heap_primary_section_list =
cv_heap_section_list_initializer_;

static cv_mutex cv_heap_primary_mutex = cv_mutex_initializer_;

static long g_heap_primary_max = (1024L * 1024L);

cv_bool cv_heap_primary_load(void)
{
    cv_heap_section_desc o_desc = cv_heap_section_desc_initializer_;
    o_desc.i_grow_len = g_heap_primary_max;
    cv_heap_section_list_init(&g_heap_primary_section_list, &o_desc);
    return cv_true;
}

void cv_heap_primary_unload(void)
{
    cv_heap_section_list_cleanup(&g_heap_primary_section_list);
}

static void cv_heap_primary_lock(void)
{
    cv_mutex_lock(&cv_heap_primary_mutex);
}

static void cv_heap_primary_unlock(void)
{
    cv_mutex_unlock(&cv_heap_primary_mutex);
}

static void * cv_heap_primary_alloc_cb(
    long i_count)
{
    void * p_buffer = cv_null_;
    p_buffer = cv_heap_section_list_alloc(&g_heap_primary_section_list,
        i_count);
    return p_buffer;
}

void * cv_heap_primary_alloc(
    long i_count)
{
    void * p_buffer = cv_null_;
    if ((i_count > 0) && (i_count <= g_heap_primary_max)) {
        cv_heap_primary_lock();
        p_buffer = cv_heap_primary_alloc_cb(i_count);
        cv_heap_primary_unlock();
    }
    return p_buffer;
}
