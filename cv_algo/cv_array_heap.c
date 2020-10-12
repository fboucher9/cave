/* See LICENSE for license details */

#include <cv_algo/cv_array_heap.h>

#include <cv_algo/cv_array_tool.h>

#include <cv_heap/cv_heap.h>

#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_array_heap", sizeof(cv_array_heap));

static cv_bool cv_array_heap_realloc(
    cv_array_heap * p_this,
    cv_uptr i_length)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    if (i_length > 0) {
        cv_array_ptr o_array_ptr;
        o_array_ptr.p_void = cv_heap_alloc(i_length, "cv_array_heap", 0);
        if (o_array_ptr.p_void) {
            cv_array_init_vector(&p_this->o_array,
                o_array_ptr.p_void, i_length);
            b_result = cv_true;
        } else {
            cv_debug_msg_(cv_debug_code_out_of_memory);
        }
    } else {
        cv_array_init(&p_this->o_array);
        b_result = cv_true;
    }
    return b_result;
}

/*

*/
cv_bool cv_array_heap_init(
    cv_array_heap * p_this,
    cv_uptr i_length)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    {
        cv_debug_construct_(g_class, p_this);
        if (cv_array_heap_realloc(p_this, i_length)) {
            b_result = cv_true;
        }
        if (!b_result) {
            cv_debug_destruct_(g_class, p_this);
        }
    }
    return b_result;
} /* _init() */

/*
 *
 */

cv_bool cv_array_heap_init_dup( cv_array_heap * p_this,
    cv_array const * p_array) {
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr );
    {
        cv_uptr i_length = 0;
        if (p_array) {
            i_length = cv_array_len(p_array);
        }
        if (cv_array_heap_init( p_this, i_length)) {
            cv_array_copy( &p_this->o_array, p_array );
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_array_heap_init_move( cv_array_heap * p_this,
    cv_array_heap * p_other) {
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && p_other, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_array_init(&p_this->o_array);
    cv_array_move(&p_this->o_array, &p_other->o_array);
    b_result = cv_true;
    return b_result;
}

/*

Free resources allocated for cv_array_heap object.

*/
void cv_array_heap_cleanup(
    cv_array_heap * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.pc_void) {
        cv_heap_free(p_this->o_array.o_min.p_void);
    }
    cv_array_cleanup(&p_this->o_array);
    cv_debug_destruct_(g_class, p_this);
} /* _cleanup() */

/* Get length of array_heap */
cv_uptr cv_array_heap_len(
    cv_array_heap const * p_this)
{
    cv_uptr i_len = 0;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    i_len = cv_array_len( &p_this->o_array);
    return i_len;
}

/* eof: cv_array_heap.c */
