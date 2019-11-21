/* See LICENSE for license details */

#include <cv_node.h>

#include <cv_null.h>

cv_bool cv_node_init(
    cv_node * p_this)
{
    cv_bool b_result = cv_false_;
    if (p_this)
    {
        p_this->o_next.p_node = p_this;
        p_this->o_prev.p_node = p_this;
        b_result = cv_true_;
    }
    return b_result;
}

void cv_node_cleanup(
    cv_node * p_this)
{
    if (p_this)
    {
        cv_node_join(p_this, p_this);
        p_this->o_next.p_node = cv_null_;
        p_this->o_prev.p_node = cv_null_;
    }
}

void cv_node_join(
    cv_node * p_left,
    cv_node * p_right)
{
    if (p_left && p_right)
    {
        cv_node * const p_left_next = p_left->o_next.p_node;
        cv_node * const p_right_prev = p_right->o_prev.p_node;
        if (p_left_next && p_right_prev)
        {
            p_left_next->o_prev.p_node = p_right->o_prev.p_node;
            p_right_prev->o_next.p_node = p_left->o_next.p_node;
            p_left->o_next.p_node = p_right;
            p_right->o_prev.p_node = p_left;
        }
    }
}

