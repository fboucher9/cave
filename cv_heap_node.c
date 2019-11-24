/* See LICENSE for license details */

#include <cv_heap_node.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

#include <cv_heap_primary.h>

#include <cv_heap_node_ptr.h>

#include <cv_null.h>

cv_bool cv_heap_node_init(
    cv_heap_node * p_this,
    long i_len)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        cv_memory_zero(p_this, cv_sizeof_(cv_heap_node));
        if (cv_node_init(&p_this->o_node))
        {
            p_this->i_len = i_len;
            b_result = cv_true;
        }
    }
    return b_result;
}

cv_heap_node * cv_heap_node_create(
    long i_len)
{
    cv_heap_node * p_this = cv_null_;
    if (i_len)
    {
        cv_heap_node_ptr o_heap_ptr = cv_heap_node_ptr_null_;

        long const i_node_len = cv_sizeof_(cv_heap_node) + i_len;

        o_heap_ptr.o_node_ptr.p_void = cv_heap_primary_alloc(i_node_len);

        if (o_heap_ptr.o_node_ptr.p_void)
        {
            if (cv_heap_node_init(o_heap_ptr.p_heap_node, i_len))
            {
                p_this = o_heap_ptr.p_heap_node;
            }
        }
    }
    return p_this;
}

