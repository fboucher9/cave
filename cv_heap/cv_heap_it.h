/* See LICENSE for license details */

#ifndef cv_heap_it_h_
#define cv_heap_it_h_

#include <cv_heap/cv_heap_pred.h>
#include <cv_algo/cv_list_it.h>
#include <cv_bool.h>

struct cv_heap_it {
    cv_list_it o_list_it;
};

#define cv_heap_it_initializer_ { cv_list_it_initializer_ }

void cv_heap_it_init(
    cv_heap_it * p_this,
    cv_list_root const * p_list);

void cv_heap_it_cleanup(
    cv_heap_it * p_this);

cv_bool cv_heap_it_next(
    cv_heap_it * p_this,
    cv_heap_node_ptr * r_ptr);

#endif /* #ifndef cv_heap_it_h_ */
