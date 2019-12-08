/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap_secondary.h>

static long const g_heap_secondary_grow_len = 4096L;

cv_bool cv_heap_secondary_init( cv_heap_secondary * p_this) {
    cv_bool b_result = cv_false;
    cv_heap_section_desc o_desc = cv_heap_section_desc_initializer_;
    o_desc.i_grow_len = g_heap_secondary_grow_len;
    if (cv_heap_section_lock_init(&p_this->o_heap_section_lock,
            &o_desc)) {
        b_result = cv_true;
    }
    return b_result;
}

void cv_heap_secondary_cleanup( cv_heap_secondary * p_this) {
    cv_heap_section_lock_cleanup(&p_this->o_heap_section_lock);
}

void * cv_heap_secondary_alloc( cv_heap_secondary * p_this, long i_len) {
    return cv_heap_section_lock_alloc(&p_this->o_heap_section_lock, i_len);
}
