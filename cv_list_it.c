/* See LICENSE for license details */

#include <cv_list_it.h>

#include <cv_list_node.h>

#include <cv_list_root.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

#include <cv_null.h>

void cv_list_it_init(
    cv_list_it * p_this,
    cv_list_root const * p_list)
{
    cv_debug_assert_( p_this && p_list, "null ptr");
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    p_this->o_cur.pc_node = & p_list->o_node;
    p_this->o_list.pc_node = & p_list->o_node;
}

void cv_list_it_cleanup(
    cv_list_it * p_this)
{
    cv_debug_assert_( !!p_this, "null ptr");
    p_this->o_cur.p_void = cv_null_;
    p_this->o_list.p_void = cv_null_;
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

cv_bool cv_list_it_first(
    cv_list_it * p_this,
    cv_list_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, "null ptr");
    p_this->o_cur = p_this->o_list;
    b_result = cv_list_it_next(p_this, r_cur);
    return b_result;
}

cv_bool cv_list_it_last(
    cv_list_it * p_this,
    cv_list_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(!!p_this, "null ptr");
    p_this->o_cur = p_this->o_list;
    b_result = cv_list_it_prev(p_this, r_cur);
    return b_result;
}

static cv_bool cv_list_it_cur(
    cv_list_it const * p_this,
    cv_list_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && r_cur, "null ptr");
    r_cur->p_void = cv_null_;
    if (p_this->o_cur.pc_node != p_this->o_list.pc_node) {
        *r_cur = p_this->o_cur;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_list_it_next(
    cv_list_it * p_this,
    cv_list_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && p_this->o_cur.pc_node, "null ptr");
    p_this->o_cur = p_this->o_cur.pc_node->o_next;
    b_result = cv_list_it_cur(p_this, r_cur);
    return b_result;
}

cv_bool cv_list_it_prev(
    cv_list_it * p_this,
    cv_list_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && p_this->o_cur.pc_node, "null ptr");
    p_this->o_cur = p_this->o_cur.pc_node->o_prev;
    b_result = cv_list_it_cur(p_this, r_cur);
    return b_result;
}

