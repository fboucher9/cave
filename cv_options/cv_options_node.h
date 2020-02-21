/* See LICENSE for license details */

#ifndef cv_options_node_h_
#define cv_options_node_h_

#include <cv_options/cv_options_pred.h>

#include <cv_algo/cv_list_node.h>

#include <cv_algo/cv_buffer.h>

struct cv_options_node
{
    cv_list_node o_node;
    /* -- */
    cv_buffer o_buffer;
};

cv_options_node * cv_options_node_create(
    cv_options_node_desc const * p_desc);

void cv_options_node_destroy(
    cv_options_node * p_this);

#endif /* #ifndef cv_options_node_h_ */
