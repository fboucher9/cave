/* See LICENSE for license details */

#include <cv_algo/cv_array.h>

#include <cv_memory.h>

#include <cv_debug.h>

#include <cv_misc/cv_sizeof.h>

#include <cv_misc/cv_limits.h>

void cv_array_init(
    cv_array * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_array_init_range(p_this,
            cv_null_, cv_null_);
}

void cv_array_init_ref(
    cv_array * p_this,
    cv_array const * p_ref)
{
    cv_debug_assert_( p_this && p_ref, cv_debug_code_null_ptr);
    cv_array_init_range(p_this,
            p_ref->o_min.pc_void,
            p_ref->o_max.pc_void);
}

void cv_array_init_vector(
    cv_array * p_this,
    void const * p_buf,
    long i_buf_len)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_assert_( 0 <= i_buf_len, cv_debug_code_invalid_length);
    {
        cv_array_ptr o_buf_ptr = cv_ptr_null_;
        o_buf_ptr.pc_void = p_buf;
        cv_array_init_range(p_this,
                o_buf_ptr.pc_char,
                o_buf_ptr.pc_char + i_buf_len);
    }
}

void cv_array_cleanup(
    cv_array * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    p_this->o_min.pc_void = cv_null_;
    p_this->o_max.pc_void = cv_null_;
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

void cv_array_init_range(
    cv_array * p_this,
    void const * p_ref_min,
    void const * p_ref_max)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    p_this->o_min.pc_void = p_ref_min;
    p_this->o_max.pc_void = p_ref_max;
}

void cv_array_init_0(
    cv_array * p_this,
    char const * p_ref0,
    long i_ref0_max_len)
{
    cv_debug_assert_( p_this && p_ref0, cv_debug_code_null_ptr);
    cv_debug_assert_( i_ref0_max_len > 0, cv_debug_code_invalid_length);
    {
        long i_ref0_len = cv_memory_find_0(p_ref0, i_ref0_max_len);
        if (i_ref0_len < 0) {
            i_ref0_len = 0;
        }
        cv_array_init_range(p_this,
                p_ref0,
                p_ref0 + i_ref0_len);
    }
}

long cv_array_len(
    cv_array const * p_this)
{
    long i_count = 0;
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    i_count = ((
        p_this->o_max.pc_char
        - p_this->o_min.pc_char) & cv_signed_long_max_);
    return i_count;
}

/* end-of-file: cv_array.c */
