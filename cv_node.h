/* See LICENSE for license details */

#ifndef cv_node_h_
#define cv_node_h_

#include <cv_node_pred.h>

#include <cv_node_ptr.h>

struct cv_node
{
    cv_node_ptr o_next;
    cv_node_ptr o_prev;
};

void cv_node_init(
    cv_node * p_this);

void cv_node_cleanup(
    cv_node * p_this);

void cv_node_join(
    cv_node * p_left,
    cv_node * p_right);

#endif /* #ifndef cv_node_h_ */
