/* See LICENSE for license details */

#include <cv_string.h>

#include <cv_memory.h>

#include <cv_null.h>

#include <cv_cast.h>

cv_bool cv_string_init(
    cv_string * p_string)
{
    cv_bool b_result = cv_false;
    if (p_string)
    {
        p_string->o_min.pc_void = cv_null_;
        p_string->o_max.pc_void = cv_null_;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_string_setup(
    cv_string * p_string,
    void const * p_ref_min,
    void const * p_ref_max)
{
    cv_bool b_result = cv_false;
    if (p_string)
    {
        p_string->o_min.pc_void = p_ref_min;
        p_string->o_max.pc_void = p_ref_max;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_string_setup0(
    cv_string * p_string,
    char const * p_ref0)
{
    cv_bool b_result = cv_false;
    if (p_string)
    {
        long const i_ref0_len = cv_memory_find0(p_ref0,
            0x7FFFFFFFL);
        p_string->o_min.pc_char = p_ref0;
        p_string->o_max.pc_char = p_ref0 + i_ref0_len;
        b_result = cv_true;
    }
    return b_result;
}

void cv_string_cleanup(
    cv_string * p_string)
{
    if (p_string)
    {
        p_string->o_min.p_void = cv_null_;
        p_string->o_max.p_void = cv_null_;
    }
}

long cv_string_len(
    cv_string const * p_string)
{
    long i_string_length = 0;
    if (p_string)
    {
        i_string_length = (
            p_string->o_max.pc_uchar
            - p_string->o_min.pc_uchar) & 0x7FFFFFFFL;
    }
    return i_string_length;
}

