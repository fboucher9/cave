/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_pool.h>
#include <cv_heap/cv_heap.h>
#include <cv_debug/cv_debug.h>
#include <cv_algo/cv_unique.h>

cv_debug_decl_(g_class);

/*
 *
 */

void cv_pool_init( cv_pool * p_this, cv_pool_desc const * p_desc) {
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_pool_desc_init(&p_this->o_desc);
    p_this->o_desc = *p_desc;
    cv_stack_init(&p_this->o_free_list);
}

/*
 *
 */

void cv_pool_cleanup( cv_pool * p_this) {
    /* Free items */
    cv_stack_ptr o_stack_ptr = {0};
    while (cv_stack_pop(&p_this->o_free_list, &o_stack_ptr)) {
        cv_stack_cleanup(o_stack_ptr.p_stack);
        cv_heap_free(o_stack_ptr.p_void);
    }
    cv_stack_cleanup(&p_this->o_free_list);
    cv_pool_desc_cleanup(&p_this->o_desc);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

void * cv_pool_alloc( cv_pool * p_this) {
    void * p_result = 0;
    cv_stack_ptr o_stack_ptr = {0};
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (cv_stack_pop(&p_this->o_free_list, &o_stack_ptr)) {
        cv_stack_cleanup(o_stack_ptr.p_stack);
        p_result = o_stack_ptr.p_void;
    } else {
        static unsigned char const a_pool_class[] = {
            'p', 'o', 'o', 'l' };
        static cv_unique g_pool_unique =
            cv_unique_initializer_(a_pool_class);
        cv_unique_next(&g_pool_unique);
        p_result = cv_heap_alloc(p_this->o_desc.i_len, &g_pool_unique);
        if (p_result) {
        } else {
            cv_debug_msg_(cv_debug_code_out_of_memory);
        }
    }
    return p_result;
}

/*
 *
 */

void cv_pool_free( cv_pool * p_this, void * p_buffer) {
    cv_stack_ptr o_stack_ptr = {0};
    cv_debug_assert_(p_this && p_buffer, cv_debug_code_null_ptr);
    o_stack_ptr.p_void = p_buffer;
    cv_stack_init(o_stack_ptr.p_stack);
    cv_stack_push(&p_this->o_free_list, o_stack_ptr.p_stack);
}

/* end-of-file: cv_pool.c */
