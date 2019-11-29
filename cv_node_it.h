/* See LICENSE for license details */

#ifndef cv_node_it_h_
#define cv_node_it_h_

/*

Base iterator for linked lists.

*/

#include <cv_list_pred.h>

#include <cv_node_pred.h>

#include <cv_node_ptr.h>

#include <cv_bool.h>

struct cv_node_it
{
    cv_node_ptr o_cur;
    cv_node_ptr o_list;
};

#define cv_node_it_initializer_ { cv_ptr_null_, cv_ptr_null_ }

void cv_node_it_init(
    cv_node_it * p_this,
    cv_list const * p_list);

void cv_node_it_cleanup(
    cv_node_it * p_this);

cv_bool cv_node_it_first(
    cv_node_it * p_this,
    cv_node_ptr * r_cur);

cv_bool cv_node_it_last(
    cv_node_it * p_this,
    cv_node_ptr * r_cur);

cv_bool cv_node_it_next(
    cv_node_it * p_this,
    cv_node_ptr * r_cur);

cv_bool cv_node_it_prev(
    cv_node_it * p_this,
    cv_node_ptr * r_cur);

#endif /* #ifndef cv_node_it_h_ */
