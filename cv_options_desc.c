/* See LICENSE for license details */

#include <cv_options_desc.h>

#include <cv_null.h>

cv_bool cv_options_desc_init(
    cv_options_desc * p_options_desc,
    char const * const * p_args_min,
    char const * const * p_args_max)
{
    cv_bool b_result = cv_false;
    if (p_options_desc)
    {
        if (cv_array_init(&p_options_desc->o_array,
                p_args_min,
                p_args_max))
        {
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_options_desc_cleanup(
    cv_options_desc * p_options_desc)
{
    if (p_options_desc)
    {
        cv_array_cleanup(&p_options_desc->o_array);
    }
}

