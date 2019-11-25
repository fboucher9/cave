/* See LICENSE for license details */

#include <cv_options_node.h>

#include <cv_options_node_desc.h>

#include <cv_options_pool.h>

#include <cv_null.h>

#include <cv_array.h>

#include <cv_memory.h>

#include <cv_list.h>

#include <cv_sizeof.h>

static cv_bool cv_options_node_init_node(
    cv_options_node * p_this,
    cv_list * p_parent)
{
    cv_bool b_result = cv_false;
    if (p_this && p_parent)
    {
        cv_node_init(&(p_this->o_node));
        cv_node_join(&(p_this->o_node), &p_parent->o_node);
        b_result = cv_true;
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
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    if (p_this && p_array)
    {
        if (cv_buffer_init(&p_this->o_buffer))
        {
            long const i_array_len = cv_array_char_count(p_array);
            if (cv_buffer_realloc(&p_this->o_buffer, i_array_len))
            {
                if (i_array_len)
                {
                    cv_memory_copy(
                        p_this->o_buffer.o_array.o_min.p_void,
                        i_array_len,
                        p_array->o_min.pc_void,
                        i_array_len);
                }
                b_result = cv_true;
            }
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
    if (p_this)
    {
        cv_memory_zero(p_this, cv_sizeof_(cv_options_node));
        if (p_desc)
        {
            if (cv_options_node_init_node(p_this, p_desc->p_parent))
            {
                if (cv_options_node_init_buf0(p_this, p_desc->p_array))
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

