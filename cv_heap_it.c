/* See LICENSE for license details */

#include <cv_heap_it.h>

#include <cv_heap_node_ptr.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

void cv_heap_it_init(
    cv_heap_it * p_this,
    cv_list const * p_list)
{
    cv_debug_assert_(
        !!p_this,
        "null ptr");
    {
        cv_debug_init_(p_this, cv_sizeof_(*p_this));
        cv_node_it_init(
            &p_this->o_node_it,
            p_list);
    }
}

void cv_heap_it_cleanup(
    cv_heap_it * p_this)
{
    cv_debug_assert_(!!p_this, "null ptr");
    {
        cv_node_it_cleanup(
            &p_this->o_node_it);
        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
}

cv_bool cv_heap_it_next(
    cv_heap_it * p_this,
    cv_heap_node_ptr * r_ptr)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, "null ptr");
    {
        b_result = cv_node_it_next(
            &p_this->o_node_it,
            &r_ptr->o_node_ptr);
    }
    return b_result;
}

