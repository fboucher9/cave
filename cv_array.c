/* See LICENSE for license details */

#include <cv_array.h>

#include <cv_memory.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

cv_bool cv_array_init(
    cv_array * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        if (cv_array_init_range(p_this,
                cv_null_, cv_null_))
        {
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_init_ref(
    cv_array * p_this,
    cv_array const * p_ref)
{
    cv_bool b_result = cv_false;
    if (p_this && p_ref)
    {
        if (cv_array_init_range(p_this,
                p_ref->o_min.pc_void,
                p_ref->o_max.pc_void))
        {
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_init_vector(
    cv_array * p_this,
    void const * p_buf,
    long i_buf_len)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        cv_array_ptr o_buf_ptr = cv_ptr_null_;
        o_buf_ptr.pc_void = p_buf;
        if (cv_array_init_range(p_this,
                o_buf_ptr.pc_char,
                o_buf_ptr.pc_char + i_buf_len))
        {
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

void cv_array_cleanup(
    cv_array * p_this)
{
    if (p_this)
    {
        p_this->o_min.pc_void = cv_null_;
        p_this->o_max.pc_void = cv_null_;
        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
}

cv_bool cv_array_init_range(
    cv_array * p_this,
    void const * p_ref_min,
    void const * p_ref_max)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        cv_debug_init_(p_this, cv_sizeof_(*p_this));
        p_this->o_min.pc_void = p_ref_min;
        p_this->o_max.pc_void = p_ref_max;
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_init_0(
    cv_array * p_this,
    char const * p_ref0,
    long i_ref0_max_len)
{
    cv_bool b_result = cv_false;
    if (p_this && p_ref0 && i_ref0_max_len)
    {
        long const i_ref0_len = cv_memory_find_0(p_ref0,
            i_ref0_max_len);
        if (i_ref0_len >= 0)
        {
            if (cv_array_init_range(p_this,
                    p_ref0,
                    p_ref0 + i_ref0_len))
            {
                b_result = cv_true;
            }
            else
            {
                cv_debug_msg_("setup failed");
            }
        }
        else
        {
            cv_debug_msg_("not zero terminated");
        }
    }
    else
    {
        cv_debug_msg_("empty ref0");
    }
    return b_result;
}

long cv_array_len(
    cv_array const * p_this)
{
    long i_count = 0;
    if (p_this)
    {
        i_count = ((
            p_this->o_max.pc_char
            - p_this->o_min.pc_char) & 0x7FFFFFFFL);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return i_count;
}

/* end-of-file: cv_array.c */
