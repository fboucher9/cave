/* See LICENSE for license details */

#include <cv_node.h>

void cv_node_init(
    cv_node * p_this)
{
    if (p_this)
    {
        p_this->p_next = p_this;
        p_this->p_prev = p_this;
    }
}

void cv_node_cleanup(
    cv_node * p_this)
{
    if (p_this)
    {
        cv_node_join(p_this, p_this);
    }
}

void cv_node_join(
    cv_node * p_left,
    cv_node * p_right)
{
    if (p_left && p_right)
    {
        cv_node * const p_left_next = p_left->p_next;
        cv_node * const p_right_prev = p_right->p_prev;
        if (p_left_next && p_right_prev)
        {
            p_left_next->p_prev = p_right->p_prev;
            p_right_prev->p_next = p_left->p_next;
            p_left->p_next = p_right;
            p_right->p_prev = p_left;
        }
    }
}

