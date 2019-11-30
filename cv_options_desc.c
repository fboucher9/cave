/* See LICENSE for license details */

#include <cv_options_desc.h>

#include <cv_null.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

void cv_options_desc_init(
    cv_options_desc * p_options_desc,
    char const * const * p_args_min,
    char const * const * p_args_max)
{
    cv_debug_assert_( !!p_options_desc, "null ptr");
    cv_debug_init_(p_options_desc, cv_sizeof_(*p_options_desc));
    cv_array_init_range(&p_options_desc->o_array,
            p_args_min,
            p_args_max);
}

void cv_options_desc_cleanup(
    cv_options_desc * p_options_desc)
{
    cv_debug_assert_( !!p_options_desc, "null ptr");
    cv_array_cleanup(&p_options_desc->o_array);
    cv_debug_cleanup_(p_options_desc, cv_sizeof_(*p_options_desc));
}

