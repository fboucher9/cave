/* See LICENSE for license details */

#ifndef cv_list_it_h_
#define cv_list_it_h_

/*

Base iterator for linked lists.

*/

#include <cv_list_pred.h>

#include <cv_list_ptr.h>

#include <cv_bool.h>

struct cv_list_it
{
    cv_list_ptr o_cur;
    cv_list_ptr o_list;
};

#define cv_list_it_initializer_ { cv_ptr_null_, cv_ptr_null_ }

void cv_list_it_init(
    cv_list_it * p_this,
    cv_list_root const * p_list);

void cv_list_it_cleanup(
    cv_list_it * p_this);

cv_bool cv_list_it_first(
    cv_list_it * p_this,
    cv_list_ptr * r_cur);

cv_bool cv_list_it_last(
    cv_list_it * p_this,
    cv_list_ptr * r_cur);

cv_bool cv_list_it_next(
    cv_list_it * p_this,
    cv_list_ptr * r_cur);

cv_bool cv_list_it_prev(
    cv_list_it * p_this,
    cv_list_ptr * r_cur);

#endif /* #ifndef cv_list_it_h_ */
