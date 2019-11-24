/* See LICENSE for license details */

#include <cv_array.h>

cv_bool cv_array_init(
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

void cv_array_cleanup(
    cv_array * p_array)
{
    if (p_array)
    {
        p_array->o_min.pc_void = cv_null_;
        p_array->o_max.pc_void = cv_null_;
    }
}

