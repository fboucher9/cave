/* See LICENSE for license details */

#include <cv_options_node.h>

#include <cv_options_node_desc.h>

#include <cv_options_pool.h>

#include <cv_null.h>

#include <cv_string.h>

#include <cv_memory.h>

#include <cv_list.h>

#include <cv_sizeof.h>

static cv_bool cv_options_node_init_node(
    cv_options_node * p_this,
    cv_list * p_parent)
{
    cv_bool b_result = cv_false_;
    if (p_this && p_parent)
    {
        cv_node_init(&(p_this->o_node));
        cv_node_join(&(p_this->o_node), &p_parent->o_node);
        b_result = cv_true_;
    }
    return b_result;
}

static void cv_options_node_cleanup_node(
    cv_options_node * p_this)
{
    if (p_this)
    {
        cv_node_cleanup(&(p_this->o_node));
    }
}

static cv_bool cv_options_node_init_buf0(
    cv_options_node * p_this,
    cv_string const * p_string)
{
    cv_bool b_result = cv_false_;
    if (p_this && p_string)
    {
        if (cv_string0_init(&(p_this->o_buf0), p_string))
        {
            b_result = cv_true_;
        }
    }
    return b_result;
}

static void cv_options_node_cleanup_buf0(
    cv_options_node * p_this)
{
    if (p_this)
    {
        cv_string0_cleanup(&(p_this->o_buf0));
    }
}

static cv_bool cv_options_node_init(
    cv_options_node * p_this,
    cv_options_node_desc const * p_desc)
{
    cv_bool b_result = cv_false_;
    if (p_this)
    {
        cv_memory_zero(p_this, cv_sizeof_(cv_options_node));
        if (p_desc)
        {
            if (cv_options_node_init_node(p_this, p_desc->p_parent))
            {
                if (cv_options_node_init_buf0(p_this, p_desc->p_string))
                {
                    b_result = cv_true_;
#if 0
                    if (!b_result)
                    {
                        cv_options_node_cleanup_buf0(p_this);
                    }
#endif
                }
                if (!b_result)
                {
                    cv_options_node_cleanup_node(p_this);
                }
            }
        }
    }
    return b_result;
}

static void cv_options_node_cleanup(
    cv_options_node * p_this)
{
    if (p_this)
    {
        cv_options_node_cleanup_buf0(p_this);
        cv_options_node_cleanup_node(p_this);
    }
}

cv_options_node * cv_options_node_create(
    cv_options_node_desc const * p_desc)
{
    cv_options_node * p_this = cv_null_;
    if (p_desc)
    {
        p_this = cv_options_pool_alloc();
        if (p_this)
        {
            if (cv_options_node_init(p_this, p_desc))
            {
            }
            else
            {
                cv_options_pool_free(p_this);
                p_this = cv_null_;
            }
        }
    }
    return p_this;
}

void cv_options_node_destroy(
    cv_options_node * p_this)
{
    if (p_this)
    {
        cv_options_node_cleanup(p_this);
        cv_options_pool_free(p_this);
    }
}

