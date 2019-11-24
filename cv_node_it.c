/* See LICENSE for license details */

#include <cv_node_it.h>

#include <cv_node.h>

#include <cv_list.h>

#include <cv_null.h>

cv_bool cv_node_it_init(
    cv_node_it * p_this,
    cv_list const * p_list)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        p_this->o_cur.p_void = cv_null_;
        p_this->o_list.p_void = cv_null_;
        if (p_list)
        {
            p_this->o_cur.pc_node = & p_list->o_node;
            p_this->o_list.pc_node = & p_list->o_node;
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_node_it_cleanup(
    cv_node_it * p_this)
{
    if (p_this)
    {
        p_this->o_cur.p_void = cv_null_;
        p_this->o_list.p_void = cv_null_;
    }
}

cv_bool cv_node_it_first(
    cv_node_it * p_this,
    cv_node_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        p_this->o_cur = p_this->o_list;
        b_result = cv_node_it_next(p_this, r_cur);
    }
    return b_result;
}

cv_bool cv_node_it_last(
    cv_node_it * p_this,
    cv_node_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        p_this->o_cur = p_this->o_list;
        b_result = cv_node_it_prev(p_this, r_cur);
    }
    return b_result;
}

static cv_bool cv_node_it_cur(
    cv_node_it const * p_this,
    cv_node_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    if (p_this && r_cur)
    {
        r_cur->p_void = cv_null_;
        if (p_this->o_cur.pc_node != p_this->o_list.pc_node)
        {
            *r_cur = p_this->o_cur;
            b_result = cv_true;
        }
    }
    return b_result;
}

cv_bool cv_node_it_next(
    cv_node_it * p_this,
    cv_node_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    if (p_this && p_this->o_cur.pc_node)
    {
        p_this->o_cur = p_this->o_cur.pc_node->o_next;
        b_result = cv_node_it_cur(p_this, r_cur);
    }
    return b_result;
}

cv_bool cv_node_it_prev(
    cv_node_it * p_this,
    cv_node_ptr * r_cur)
{
    cv_bool b_result = cv_false;
    if (p_this && p_this->o_cur.pc_node)
    {
        p_this->o_cur = p_this->o_cur.pc_node->o_prev;
        b_result = cv_node_it_cur(p_this, r_cur);
    }
    return b_result;
}

