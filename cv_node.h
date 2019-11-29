/* See LICENSE for license details */

#ifndef cv_node_h_
#define cv_node_h_

/*

Base object for linked lists.  The linked list is implemented with two
pointers, next and prev.  The cv_node structure represents both the parent and
the node header.  The cv_node_ptr union is used to cast the pointers.  A
single cv_node_join function is used to insert and remove nodes.

*/

#include <cv_node_pred.h>

#include <cv_node_ptr.h>

#include <cv_bool.h>

struct cv_node
{
    cv_node_ptr o_next;
    cv_node_ptr o_prev;
};

#define cv_node_initializer_ { cv_ptr_null_, cv_ptr_null_ }

void cv_node_init(
    cv_node * p_this);

void cv_node_cleanup(
    cv_node * p_this);

void cv_node_join(
    cv_node * p_left,
    cv_node * p_right);

#endif /* #ifndef cv_node_h_ */
