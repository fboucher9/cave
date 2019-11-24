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
        if (cv_array_init(&p_string->o_array))
        {
            b_result = cv_true;
        }
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
        if (cv_array_setup(&p_string->o_array,
                p_ref_min,
                p_ref_max))
        {
            b_result = cv_true;
        }
    }
    return b_result;
}

cv_bool cv_string_setup0(
    cv_string * p_string,
    char const * p_ref0,
    long i_ref0_max_len)
{
    cv_bool b_result = cv_false;
    if (p_string)
    {
        long const i_ref0_len = cv_memory_find0(p_ref0,
            i_ref0_max_len);
        if (cv_array_setup(&p_string->o_array,
                p_ref0,
                p_ref0 + i_ref0_len))
        {
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_string_cleanup(
    cv_string * p_string)
{
    if (p_string)
    {
        cv_array_cleanup(&p_string->o_array);
    }
}

long cv_string_len(
    cv_string const * p_string)
{
    long i_string_length = 0;
    if (p_string)
    {
        i_string_length = cv_array_char_count(&p_string->o_array);
    }
    return i_string_length;
}

