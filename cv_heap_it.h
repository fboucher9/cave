/* See LICENSE for license details */

#ifndef cv_heap_it_h_
#define cv_heap_it_h_

#include <cv_heap_pred.h>

#include <cv_node_it.h>

struct cv_heap_it
{
    cv_node_it o_node_it;
};

char cv_heap_it_init(
    cv_heap_it * p_this,
    cv_list const * p_list);

void cv_heap_it_cleanup(
    cv_heap_it * p_this);

char cv_heap_it_next(
    cv_heap_it * p_this,
    cv_heap_node_ptr * r_ptr);

#endif /* #ifndef cv_heap_it_h_ */
