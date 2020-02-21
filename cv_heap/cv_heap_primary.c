/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap/cv_heap_primary.h>

static cv_uptr const g_heap_primary_max = (4096L);

static cv_uptr const g_heap_primary_grow_len = (1024L * 1024L);

cv_bool cv_heap_primary_init(cv_heap_primary * p_this) {
    cv_heap_section_desc o_desc = {0};
    o_desc.i_grow_len = g_heap_primary_grow_len;
    cv_heap_section_lock_init(&p_this->o_heap_section_lock, &o_desc);
    return cv_true;
}

void cv_heap_primary_cleanup(cv_heap_primary * p_this) {
    cv_heap_section_lock_cleanup(&p_this->o_heap_section_lock);
}

void * cv_heap_primary_alloc(cv_heap_primary * p_this, cv_uptr i_count) {
    void * p_buffer = 0;
    if ((i_count > 0) && (i_count <= g_heap_primary_max)) {
        p_buffer = cv_heap_section_lock_alloc(&p_this->o_heap_section_lock,
            i_count);
    }
    return p_buffer;
}
