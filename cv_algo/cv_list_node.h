/* See LICENSE for license details */

#ifndef cv_list_node_h_
#define cv_list_node_h_

/*

Base object for linked lists.  The linked list is implemented with two
pointers, next and prev.  The cv_list_node structure represents both the parent and
the node header.  The cv_list_ptr union is used to cast the pointers.  A
single cv_list_join function is used to insert and remove nodes.

*/

#include <cv_algo/cv_list_pred.h>

#include <cv_algo/cv_list_ptr.h>

#include <cv_misc/cv_bool.h>

struct cv_list_node
{
    cv_list_ptr o_next;
    cv_list_ptr o_prev;
};

void cv_list_node_init(
    cv_list_node * p_this);

void cv_list_node_cleanup(
    cv_list_node * p_this);

void cv_list_join(
    cv_list_node * p_left,
    cv_list_node * p_right);

#endif /* #ifndef cv_list_node_h_ */
