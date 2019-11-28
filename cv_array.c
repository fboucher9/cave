/* See LICENSE for license details */

#include <cv_array.h>

#include <cv_memory.h>

#include <cv_debug.h>

cv_bool cv_array_init(
    cv_array * p_array)
{
    cv_bool b_result = cv_false;
    if (p_array)
    {
        p_array->o_min.pc_void = cv_null_;
        p_array->o_max.pc_void = cv_null_;
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_init_ref(
    cv_array * p_array,
    cv_array const * p_ref)
{
    cv_bool b_result = cv_false;
    if (p_array && p_ref)
    {
        *p_array = *p_ref;
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

void cv_array_cleanup(
    cv_array * p_array)
{
    if (p_array)
    {
        p_array->o_min.pc_void = cv_null_;
        p_array->o_max.pc_void = cv_null_;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
}

cv_bool cv_array_init_range(
    cv_array * p_array,
    void const * p_ref_min,
    void const * p_ref_max)
{
    cv_bool b_result = cv_false;
    if (p_array)
    {
        p_array->o_min.pc_void = p_ref_min;
        p_array->o_max.pc_void = p_ref_max;
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

cv_bool cv_array_init_0(
    cv_array * p_array,
    char const * p_ref0,
    long i_ref0_max_len)
{
    cv_bool b_result = cv_false;
    if (p_array && p_ref0 && i_ref0_max_len)
    {
        long const i_ref0_len = cv_memory_find_0(p_ref0,
            i_ref0_max_len);
        if (i_ref0_len >= 0)
        {
            if (cv_array_init_range(p_array,
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
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = ((
            p_array->o_max.pc_char
            - p_array->o_min.pc_char) & 0x7FFFFFFFL);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return i_count;
}

long cv_array_short_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = ((
            p_array->o_max.pc_short
            - p_array->o_min.pc_short) & 0x7FFFFFFFL);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return i_count;
}

long cv_array_int_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = ((
            p_array->o_max.pc_int
            - p_array->o_min.pc_int) & 0x7FFFFFFFL);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return i_count;
}

long cv_array_long_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = ((
            p_array->o_max.pc_long
            - p_array->o_min.pc_long) & 0x7FFFFFFFL);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return i_count;
}

long cv_array_ll_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = ((
            p_array->o_max.pc_ll
            - p_array->o_min.pc_ll) & 0x7FFFFFFFL);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return i_count;
}

long cv_array_ptr_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = ((
            p_array->o_max.ppc_void
            - p_array->o_min.ppc_void) & 0x7FFFFFFFL);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return i_count;
}

/* end-of-file: cv_array.c */
