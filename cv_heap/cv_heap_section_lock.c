/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap/cv_heap_section_lock.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_heap_section_lock");

/*
 *
 */

cv_bool cv_heap_section_lock_init(
    cv_heap_section_lock * p_this,
    cv_heap_section_desc const * p_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    if (cv_mutex_init(&p_this->o_mutex)) {
        cv_heap_section_init(&p_this->o_heap_section, p_desc);
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

void cv_heap_section_lock_cleanup(
    cv_heap_section_lock * p_this) {
    cv_heap_section_cleanup(&p_this->o_heap_section);
    cv_mutex_cleanup(&p_this->o_mutex);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

void * cv_heap_section_lock_alloc(
    cv_heap_section_lock * p_this,
    cv_uptr i_len) {
    void * p_result = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(i_len > 0, cv_debug_code_invalid_length);
    cv_mutex_lock(&p_this->o_mutex);
    p_result = cv_heap_section_alloc(&p_this->o_heap_section, i_len);
    cv_mutex_unlock(&p_this->o_mutex);
    return p_result;
}

/* end-of-file: cv_heap_section_lock.c */
