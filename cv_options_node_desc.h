/* See LICENSE for license details */

#ifndef cv_options_node_desc_h_
#define cv_options_node_desc_h_

#include <cv_options_pred.h>

#include <cv_node_pred.h>

#include <cv_string_pred.h>

struct cv_options_node_desc
{
    cv_node * p_parent;

    cv_string const * p_string;

};

#endif /* #ifndef cv_options_node_desc_h_ */
