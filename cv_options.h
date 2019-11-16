/* See LICENSE for license details */

#ifndef cv_options_h_
#define cv_options_h_

#include <cv_options_pred.h>

#include <cv_string_pred.h>

#include <cv_options_desc.h>

#include <cv_node.h>

struct cv_options
{
    cv_options_desc o_desc;
    /* -- */
    cv_node o_list;
};

cv_options * cv_options_create(
    cv_options_desc const * p_options_desc);

void cv_options_destroy(
    cv_options * p_this);

char cv_options_add(
    cv_options * p_this,
    cv_string const * p_string);

#endif /* #ifndef cv_options_h_ */

