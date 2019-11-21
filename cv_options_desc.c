/* See LICENSE for license details */

#include <cv_options_desc.h>

#include <cv_null.h>

cv_bool cv_options_desc_init(
    cv_options_desc * p_options_desc)
{
    cv_bool b_result = cv_false_;
    if (p_options_desc)
    {
        p_options_desc->p_args_min = cv_null_;
        p_options_desc->p_args_max = cv_null_;
        b_result = cv_true_;
    }
    return b_result;
}

void cv_options_desc_cleanup(
    cv_options_desc * p_options_desc)
{
    if (p_options_desc)
    {
        p_options_desc->p_args_min = cv_null_;
        p_options_desc->p_args_max = cv_null_;
    }
}

