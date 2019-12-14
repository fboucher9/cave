/* See LICENSE for license details */

#include <cv_options/cv_options_desc.h>

#include <cv_misc/cv_null.h>

#include <cv_debug.h>

#include <cv_misc/cv_sizeof.h>

cv_debug_decl_(g_class);

void cv_options_desc_init(
    cv_options_desc * p_options_desc,
    char const * const * p_args_min,
    char const * const * p_args_max)
{
    cv_debug_assert_( !!p_options_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_options_desc);
    cv_array_init_range(&p_options_desc->o_array,
            p_args_min,
            p_args_max);
}

void cv_options_desc_cleanup(
    cv_options_desc * p_options_desc)
{
    cv_debug_assert_( !!p_options_desc, cv_debug_code_null_ptr);
    cv_array_cleanup(&p_options_desc->o_array);
    cv_debug_destruct_(g_class, p_options_desc);
}

