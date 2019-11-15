/* See LICENSE for license details */

#include <cv_options_desc.h>

#include <cv_null.h>

#include <cv_unused.h>

char cv_options_desc_init(
    cv_options_desc * p_options_desc)
{
    p_options_desc->p_args_min = cv_null_;

    p_options_desc->p_args_max = cv_null_;

    return 1;
}

void cv_options_desc_cleanup(
    cv_options_desc * p_options_desc)
{
    cv_unused_(p_options_desc);
}

