/* See LICENSE for license details */

#include <cv_algo/cv_list_node.h>

#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_list_node", sizeof(cv_list_node));

void cv_list_node_init(
    cv_list_node * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    p_this->o_next.p_node = p_this;
    p_this->o_prev.p_node = p_this;
}

void cv_list_node_cleanup(
    cv_list_node * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_list_join(p_this, p_this);
    p_this->o_next.p_node = 0;
    p_this->o_prev.p_node = 0;
    cv_debug_destruct_(g_class, p_this);
}

void cv_list_join(
    cv_list_node * p_left,
    cv_list_node * p_right)
{
    cv_debug_assert_(p_left && p_right, cv_debug_code_null_ptr);
    {
        cv_list_node * const p_left_next = p_left->o_next.p_node;
        cv_list_node * const p_right_prev = p_right->o_prev.p_node;
        cv_debug_assert_(p_left_next && p_right_prev, cv_debug_code_null_ptr);
        p_left_next->o_prev.p_node = p_right->o_prev.p_node;
        p_right_prev->o_next.p_node = p_left->o_next.p_node;
        p_left->o_next.p_node = p_right;
        p_right->o_prev.p_node = p_left;
    }
}

