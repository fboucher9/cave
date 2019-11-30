/* See LICENSE for license details */

#ifndef cv_options_node_desc_h_
#define cv_options_node_desc_h_

#include <cv_options_pred.h>

#include <cv_array.h>

struct cv_options_node_desc
{
    cv_array o_array;
};

#define cv_options_node_desc_initializer_ { cv_array_null_ }

#endif /* #ifndef cv_options_node_desc_h_ */
