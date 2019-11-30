/* See LICENSE for license details */

#include <cv_options_node.h>

#include <cv_options_node_desc.h>

#include <cv_options_pool.h>

#include <cv_null.h>

#include <cv_array.h>

#include <cv_memory.h>

#include <cv_list_root.h>

#include <cv_sizeof.h>

#include <cv_debug.h>

#include <cv_array_tool.h>

static void cv_options_node_init_node(
    cv_options_node * p_this)
{
    cv_debug_assert_(
        !!p_this,
        "null ptr");
    {
        cv_list_node_init(&(p_this->o_node));
    }
}

static void cv_options_node_cleanup_node(
    cv_options_node * p_this)
{
    if (p_this)
    {
        cv_list_node_cleanup(&(p_this->o_node));
    }
}

static cv_bool cv_options_node_init_buffer(
    cv_options_node * p_this,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(
        p_this && p_array,
        "null ptr");
    {
        long const i_array_len = cv_array_len(p_array);
        if (cv_buffer_init(&p_this->o_buffer, i_array_len))
        {
            cv_array_copy(
                &p_this->o_buffer.o_array,
                p_array);

            b_result = cv_true;
        }
    }
    return b_result;
}

static void cv_options_node_cleanup_buf0(
    cv_options_node * p_this)
{
    if (p_this)
    {
        cv_buffer_cleanup(&(p_this->o_buffer));
    }
}

static cv_bool cv_options_node_init(
    cv_options_node * p_this,
    cv_options_node_desc const * p_desc)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(
        p_this && p_desc,
        "null ptr");
    {
        cv_debug_init_(p_this, cv_sizeof_(*p_this));
        cv_options_node_init_node(p_this);
        if (cv_options_node_init_buffer(p_this, &p_desc->o_array))
        {
            b_result = cv_true;
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
            cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
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
        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
    else
    {
        cv_debug_msg_("null ptr");
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
                cv_debug_msg_("failed init");
                cv_options_pool_free(p_this);
                p_this = cv_null_;
            }
        }
        else
        {
            cv_debug_msg_("out of memory");
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
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

