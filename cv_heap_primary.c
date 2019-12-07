/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap_primary.h>
#include <cv_null.h>
#include <cv_mutex.h>
#include <cv_list_root.h>
#include <cv_list_node.h>
#include <cv_list_it.h>
#include <cv_runtime.h>
#include <cv_sizeof.h>
#include <cv_heap_section_lock.h>

static cv_heap_section_lock g_heap_primary_section_lock =
cv_heap_section_lock_initializer_;

static long g_heap_primary_max = (1024L * 1024L);

cv_bool cv_heap_primary_load(void) {
    cv_heap_section_desc o_desc = cv_heap_section_desc_initializer_;
    o_desc.i_grow_len = g_heap_primary_max;
    cv_heap_section_lock_init(&g_heap_primary_section_lock, &o_desc);
    return cv_true;
}

void cv_heap_primary_unload(void) {
    cv_heap_section_lock_cleanup(&g_heap_primary_section_lock);
}

void * cv_heap_primary_alloc(
    long i_count)
{
    void * p_buffer = cv_null_;
    if ((i_count > 0) && (i_count <= g_heap_primary_max)) {
        p_buffer = cv_heap_section_lock_alloc(&g_heap_primary_section_lock,
            i_count);
    }
    return p_buffer;
}
