/* See LICENSE for license details */

#include <cv_algo/cv_buffer.h>

#include <cv_heap/cv_heap.h>

#include <cv_null.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

static cv_bool cv_buffer_realloc(
    cv_buffer * p_this,
    long i_length)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_assert_( i_length > 0, cv_debug_code_invalid_length);
    {
        cv_array_ptr o_array_ptr = cv_ptr_null_;
        o_array_ptr.p_void = cv_heap_alloc(i_length);
        if (o_array_ptr.p_void) {
            cv_array_init_vector(&p_this->o_array,
                o_array_ptr.p_void, i_length);
            b_result = cv_true;
        } else {
            cv_debug_msg_(cv_debug_code_out_of_memory);
        }
    }
    return b_result;
}

/*

*/
cv_bool cv_buffer_init(
    cv_buffer * p_this,
    long i_length)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_assert_( i_length > 0, cv_debug_code_invalid_length);
    {
        cv_debug_init_(p_this, cv_sizeof_(*p_this));
        if (cv_buffer_realloc(p_this, i_length)) {
            b_result = cv_true;
        }
        if (!b_result) {
            cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
        }
    }
    return b_result;
} /* _init() */

/*

Free resources allocated for cv_buffer object.

*/
void cv_buffer_cleanup(
    cv_buffer * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.pc_void) {
        cv_heap_free(p_this->o_array.o_min.p_void);
    }
    cv_array_cleanup(&p_this->o_array);
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
} /* _cleanup() */

/* Get length of buffer */
long cv_buffer_len(
    cv_buffer const * p_this)
{
    long i_len = 0;
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    i_len = cv_array_len( &p_this->o_array);
    return i_len;
}

/* eof: cv_buffer.c */
