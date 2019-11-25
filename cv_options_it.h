/* See LICENSE for license details */

#ifndef cv_options_it_h_
#define cv_options_it_h_

#include <cv_options_pred.h>

#include <cv_node_it.h>

#include <cv_array_pred.h>

struct cv_options_it
{
    cv_node_it o_node_it;
};

#define cv_options_it_initializer_ { cv_node_it_initializer_ }

cv_bool cv_options_it_init(
    cv_options_it * p_this,
    cv_options const * p_options);

void cv_options_it_cleanup(
    cv_options_it * p_this);

cv_bool cv_options_it_next(
    cv_options_it * p_this,
    cv_array * r_array);

#endif /* #ifndef cv_options_it_h_ */
