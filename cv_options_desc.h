/* See LICENSE for license details */

#ifndef cv_options_desc_h_
#define cv_options_desc_h_

#include <cv_options_pred.h>

#include <cv_null.h>

#include <cv_bool.h>

#include <cv_array.h>

struct cv_options_desc
{
    cv_array o_array;
};

#define cv_options_desc_initializer_ { cv_array_null_ }

cv_bool cv_options_desc_init(
    cv_options_desc * p_options_desc,
    char const * const * p_args_min,
    char const * const * p_args_max);

void cv_options_desc_cleanup(
    cv_options_desc * p_options_desc);

#endif /* #ifndef cv_options_desc_h_ */
