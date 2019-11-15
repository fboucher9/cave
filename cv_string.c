/* See LICENSE for license details */

#include <cv_string.h>

#include <cv_unused.h>

char cv_string_init(
    cv_string * p_string,
    void const * p_ref_min,
    void const * p_ref_max)
{
    char b_result;
    p_string->o_min.pc_void = p_ref_min;
    p_string->o_max.pc_void = p_ref_max;
    b_result = 1;
    return b_result;
}

void cv_string_cleanup(
    cv_string * p_string)
{
    cv_unused_(p_string);
}

long cv_string_len(
    cv_string const * p_string)
{
    long i_string_length = 0;
    if (p_string)
    {
        i_string_length = (long)(
            p_string->o_max.pc_uchar
            - p_string->o_min.pc_uchar);
    }
    return i_string_length;
}

