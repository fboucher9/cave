/* See LICENSE for license details */

#ifndef cv_options_h_
#define cv_options_h_

#include <cv_options_pred.h>

#include <cv_array_pred.h>

#include <cv_options_desc.h>

#include <cv_list.h>

struct cv_options
{
    cv_list o_list;
};

#define cv_options_initializer_ { cv_list_initializer_ }

void cv_options_init(
    cv_options * p_this);

void cv_options_cleanup(
    cv_options * p_this);

cv_bool cv_options_setup(
    cv_options * p_this,
    cv_options_desc const * p_desc);

cv_bool cv_options_add(
    cv_options * p_this,
    cv_array const * p_array);

#endif /* #ifndef cv_options_h_ */

