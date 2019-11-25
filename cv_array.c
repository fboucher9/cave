/* See LICENSE for license details */

#include <cv_array.h>

#include <cv_memory.h>

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
}

cv_bool cv_array_setup(
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
    return b_result;
}

cv_bool cv_array_setup0(
    cv_array * p_array,
    char const * p_ref0,
    long i_ref0_max_len)
{
    cv_bool b_result = cv_false;
    if (p_array && p_ref0)
    {
        long const i_ref0_len = cv_memory_find0(p_ref0,
            i_ref0_max_len);
        if (cv_array_setup(p_array,
                p_ref0,
                p_ref0 + i_ref0_len))
        {
            b_result = cv_true;
        }
    }
    return b_result;
}

long cv_array_char_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = cv_cast_(long,
            p_array->o_max.pc_char
            - p_array->o_min.pc_char);
    }
    return i_count;
}

long cv_array_short_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = cv_cast_(long,
            p_array->o_max.pc_short
            - p_array->o_min.pc_short);
    }
    return i_count;
}

long cv_array_int_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = cv_cast_(long,
            p_array->o_max.pc_int
            - p_array->o_min.pc_int);
    }
    return i_count;
}

long cv_array_long_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = cv_cast_(long,
            p_array->o_max.pc_long
            - p_array->o_min.pc_long);
    }
    return i_count;
}

long cv_array_ll_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = cv_cast_(long,
            p_array->o_max.pc_ll
            - p_array->o_min.pc_ll);
    }
    return i_count;
}

long cv_array_ptr_count(
    cv_array const * p_array)
{
    long i_count = 0;
    if (p_array)
    {
        i_count = cv_cast_(long,
            p_array->o_max.ppc_void
            - p_array->o_min.ppc_void);
    }
    return i_count;
}

/* end-of-file: cv_array.c */
