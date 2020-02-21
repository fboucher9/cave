/* See LICENSE for license details */

#include <cv_algo/cv_array.h>

#include <cv_memory.h>

#include <cv_debug/cv_debug.h>

#include <cv_misc/cv_cast.h>

cv_debug_decl_(g_class);

void cv_array_init(
    cv_array * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_array_init_range(p_this, 0, 0);
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
    cv_uptr i_buf_len)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    {
        cv_array_ptr o_buf_ptr = {0};
        o_buf_ptr.pc_void = p_buf;
        cv_array_init_range(p_this,
                o_buf_ptr.pc_char,
                o_buf_ptr.pc_char + i_buf_len);
    }
}

void cv_array_cleanup(
    cv_array * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    p_this->o_min.pc_void = 0;
    p_this->o_max.pc_void = 0;
    cv_debug_destruct_(g_class, p_this);
}

void cv_array_init_range(
    cv_array * p_this,
    void const * p_ref_min,
    void const * p_ref_max)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    p_this->o_min.pc_void = p_ref_min;
    p_this->o_max.pc_void = p_ref_max;
}

void cv_array_init_0(
    cv_array * p_this,
    char const * p_ref0,
    cv_uptr i_ref0_max_len)
{
    cv_debug_assert_( p_this && p_ref0, cv_debug_code_null_ptr);
    cv_debug_assert_( i_ref0_max_len > 0, cv_debug_code_invalid_length);
    {
        cv_uptr i_ref0_len = cv_memory_find_0(p_ref0, i_ref0_max_len);
        cv_array_init_range(p_this,
                p_ref0,
                p_ref0 + i_ref0_len);
    }
}

cv_uptr cv_array_len(
    cv_array const * p_this)
{
    cv_uptr i_count = 0;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    i_count = cv_cast_(cv_uptr,
        p_this->o_max.pc_char - p_this->o_min.pc_char);
    return i_count;
}

/* end-of-file: cv_array.c */
