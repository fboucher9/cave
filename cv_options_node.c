/* See LICENSE for license details */

#include <cv_options_node.h>

#include <cv_options_node_desc.h>

#include <cv_null.h>

#include <cv_heap.h>

#include <cv_string.h>

#include <cv_memory.h>

static char cv_options_node_init_node(
    cv_options_node * p_this,
    cv_node * p_parent)
{
    char b_result = 0;
    if (p_this && p_parent)
    {
        cv_node_init(&(p_this->o_node));
        cv_node_join(&(p_this->o_node), p_parent);
        b_result = 1;
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

static char cv_options_node_init_buf0(
    cv_options_node * p_this,
    cv_string const * p_string)
{
    char b_result = 0;
    if (p_this && p_string)
    {
        if (cv_string0_init(&(p_this->o_buf0), p_string))
        {
            b_result = 1;
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

static char cv_options_node_init(
    cv_options_node * p_this,
    cv_options_node_desc const * p_desc)
{
    char b_result = 0;
    if (p_this)
    {
        cv_memory_zero(p_this, cv_sizeof_(cv_options_node));
        if (p_desc)
        {
            if (cv_options_node_init_node(p_this, p_desc->p_parent))
            {
                if (cv_options_node_init_buf0(p_this, p_desc->p_string))
                {
                    b_result = 1;
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
        p_this = cv_new_(cv_options_node);
        if (p_this)
        {
            if (cv_options_node_init(p_this, p_desc))
            {
            }
            else
            {
                cv_delete_(p_this);
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
        cv_delete_(p_this);
    }
}

