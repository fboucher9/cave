/* See LICENSE for license details */

#include <cv_heap_it.h>

#include <cv_heap_node_ptr.h>

cv_bool cv_heap_it_init(
    cv_heap_it * p_this,
    cv_list const * p_list)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        b_result = cv_node_it_init(
            &p_this->o_node_it,
            p_list);
    }
    return b_result;
}

void cv_heap_it_cleanup(
    cv_heap_it * p_this)
{
    if (p_this)
    {
        cv_node_it_cleanup(
            &p_this->o_node_it);
    }
}

cv_bool cv_heap_it_next(
    cv_heap_it * p_this,
    cv_heap_node_ptr * r_ptr)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        b_result = cv_node_it_next(
            &p_this->o_node_it,
            &r_ptr->o_node_ptr);
    }
    return b_result;
}

