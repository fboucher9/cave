/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap/cv_heap_secondary.h>
#include <cv_debug.h>
#include <cv_misc/cv_sizeof.h>

cv_debug_decl_(g_class);

static long const g_heap_secondary_grow_len = 4096L;

/*
 *
 */

cv_bool cv_heap_secondary_init( cv_heap_secondary * p_this) {
    cv_bool b_result = cv_false;
    cv_heap_section_desc o_desc = cv_heap_section_desc_initializer_;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    o_desc.i_grow_len = g_heap_secondary_grow_len;
    if (cv_heap_section_lock_init(&p_this->o_heap_section_lock,
            &o_desc)) {
        b_result = cv_true;
    } else {
        cv_debug_destruct_(g_class, p_this);
    }
    return b_result;
}

/*
 *
 */

void cv_heap_secondary_cleanup( cv_heap_secondary * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_heap_section_lock_cleanup(&p_this->o_heap_section_lock);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

void * cv_heap_secondary_alloc( cv_heap_secondary * p_this, long i_len) {
    void * p_result = cv_null_;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_result = cv_heap_section_lock_alloc(&p_this->o_heap_section_lock,
        i_len);
    return p_result;
}

/* end-of-file: cv_heap_secondary.c */
