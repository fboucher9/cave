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

struct cv_node
{
    cv_node_ptr o_next;
    cv_node_ptr o_prev;
};

struct cv_list
{
    cv_node o_node;
};

char cv_node_init(
    cv_node * p_this);

void cv_node_cleanup(
    cv_node * p_this);

void cv_node_join(
    cv_node * p_left,
    cv_node * p_right);

char cv_list_init(
    cv_list * p_this);

#endif /* #ifndef cv_node_h_ */
