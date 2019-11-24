/* See LICENSE for license details */

#ifndef cv_options_node_desc_h_
#define cv_options_node_desc_h_

#include <cv_options_pred.h>

#include <cv_node_pred.h>

#include <cv_string_pred.h>

#include <cv_null.h>

struct cv_options_node_desc
{
    cv_list * p_parent;

    cv_string const * p_string;

};

#define cv_options_node_desc_initializer_ { cv_null_, cv_null_ }

#endif /* #ifndef cv_options_node_desc_h_ */
