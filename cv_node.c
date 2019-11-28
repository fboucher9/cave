/* See LICENSE for license details */

#include <cv_node.h>

#include <cv_null.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

cv_bool cv_node_init(
    cv_node * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        cv_debug_init_(p_this, cv_sizeof_(*p_this));
        p_this->o_next.p_node = p_this;
        p_this->o_prev.p_node = p_this;
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
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
        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
    else
    {
        cv_debug_msg_("null ptr");
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
        else
        {
            cv_debug_msg_("join null members");
        }
    }
    else
    {
        cv_debug_msg_("join null param");
    }
}

