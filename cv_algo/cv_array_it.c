/* See LICENSE for license details */

#include <cv_algo/cv_array_it.h>

#include <cv_algo/cv_array_tool.h>

#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_array_it");

void cv_array_it_init(
    cv_array_it * p_this,
    cv_array const * p_array)
{
    cv_debug_assert_( p_this && p_array, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_array_init_ref(&p_this->o_array, p_array);
}

void cv_array_it_init_vector(
    cv_array_it * p_this,
    void const * p_buf,
    cv_uptr i_len)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_array_init_vector(&p_this->o_array, p_buf, i_len);
}

void cv_array_it_init_range(
    cv_array_it * p_this,
    void const * p_range_min,
    void const * p_range_max) {
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_array_init_range(&p_this->o_array, p_range_min, p_range_max);
}

void cv_array_it_cleanup(
    cv_array_it * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_array_cleanup(&p_this->o_array);
    cv_debug_destruct_(g_class, p_this);
}

cv_bool cv_array_it_is_done(
    cv_array_it const * p_this) {
    cv_bool b_result = cv_false;
    if (p_this->o_array.o_min.pc_uchar ==
        p_this->o_array.o_max.pc_uchar) {
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_array_it_get_next_char(
    cv_array_it * p_this,
    cv_array_ptr * r_value)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && r_value, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.pc_uchar !=
        p_this->o_array.o_max.pc_uchar) {
        *r_value = p_this->o_array.o_min;
        p_this->o_array.o_min.pc_uchar ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_array_it_get_next_ptr(
    cv_array_it * p_this,
    cv_array_ptr * r_value)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && r_value, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.pcpc_void <
        p_this->o_array.o_max.pcpc_void) {
        *r_value = p_this->o_array.o_min;
        p_this->o_array.o_min.pcpc_void ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_array_it_get_next_array(
    cv_array_it * p_this,
    cv_uptr i_array_len,
    cv_array_ptr * r_value)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && i_array_len && r_value, cv_debug_code_null_ptr);
    if ((p_this->o_array.o_min.pc_uchar + i_array_len)
        <= p_this->o_array.o_max.pc_uchar) {
        *r_value = p_this->o_array.o_min;
        p_this->o_array.o_min.pc_uchar += i_array_len;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_array_it_read_next_char(
    cv_array_it * p_this,
    unsigned char * r_value)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && r_value, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.pc_uchar !=
        p_this->o_array.o_max.pc_uchar) {
        *(r_value) = *(p_this->o_array.o_min.pc_uchar);
        p_this->o_array.o_min.pc_uchar ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_array_it_read_next_ptr(
    cv_array_it * p_this,
    void const * * r_value)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && r_value, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.pcpc_void <
        p_this->o_array.o_max.pcpc_void) {
        *(r_value) = *(p_this->o_array.o_min.pcpc_void);
        p_this->o_array.o_min.pcpc_void ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_array_it_read_next_array(
    cv_array_it * p_this,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && p_array, cv_debug_code_null_ptr);
    {
        cv_uptr const i_array_len = cv_array_len(p_array);
        if ((p_this->o_array.o_min.pc_uchar + i_array_len)
            <= p_this->o_array.o_max.pc_uchar) {
            cv_array_copy( p_array, &p_this->o_array);
            p_this->o_array.o_min.pc_uchar += i_array_len;
            b_result = cv_true;
        }
    }
    return b_result;
}

cv_bool cv_array_it_write_next_char(
    cv_array_it * p_this,
    unsigned char c_data)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.p_uchar !=
        p_this->o_array.o_max.p_uchar) {
        *(p_this->o_array.o_min.p_uchar) = c_data;
        p_this->o_array.o_min.p_uchar ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_array_it_write_next_ptr(
    cv_array_it * p_this,
    void const * pc_void)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    if (p_this->o_array.o_min.ppc_void !=
        p_this->o_array.o_max.ppc_void) {
        *(p_this->o_array.o_min.ppc_void) = pc_void;
        p_this->o_array.o_min.ppc_void ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_array_it_write_next_array(
    cv_array_it * p_this,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && p_array, cv_debug_code_null_ptr);
    {
        cv_uptr const i_array_len = cv_array_len(p_array);
        if ((p_this->o_array.o_min.p_uchar + i_array_len)
            <= p_this->o_array.o_max.p_uchar) {
            cv_array_copy( &p_this->o_array, p_array);
            p_this->o_array.o_min.p_uchar += i_array_len;
            b_result = cv_true;
        }
    }
    return b_result;
}

cv_bool cv_array_it_preview_next_char( cv_array_it * p_this,
    unsigned char * r_value) {
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    {
        if (p_this->o_array.o_min.pc_uchar !=
            p_this->o_array.o_max.pc_uchar) {
            *r_value = *p_this->o_array.o_min.pc_uchar;
            b_result = cv_true;
        }
    }
    return b_result;
}

cv_bool cv_array_it_skip_next_char( cv_array_it * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    {
        if (p_this->o_array.o_min.pc_uchar !=
            p_this->o_array.o_max.pc_uchar) {
            p_this->o_array.o_min.pc_uchar ++;
            b_result = cv_true;
        }
    }
    return b_result;
}

/* end-of-file: cv_array_it.c */
