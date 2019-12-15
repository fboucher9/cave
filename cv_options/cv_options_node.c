/* See LICENSE for license details */

#include <cv_options/cv_options_node.h>

#include <cv_options/cv_options_node_desc.h>

#include <cv_options/cv_options_pool.h>

#include <cv_misc/cv_null.h>

#include <cv_algo/cv_array.h>

#include <cv_memory.h>

#include <cv_algo/cv_list_root.h>

#include <cv_misc/cv_sizeof.h>

#include <cv_debug.h>

#include <cv_algo/cv_array_tool.h>

cv_debug_decl_(g_class);

static void cv_options_node_init_node(
    cv_options_node * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_list_node_init(&(p_this->o_node));
}

static void cv_options_node_cleanup_node(
    cv_options_node * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_list_node_cleanup(&(p_this->o_node));
}

static cv_bool cv_options_node_init_buffer(
    cv_options_node * p_this,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && p_array, cv_debug_code_null_ptr);
    {
        long const i_array_len = cv_array_len(p_array);
        if (cv_buffer_init(&p_this->o_buffer, i_array_len)) {
            cv_array_copy( &p_this->o_buffer.o_array, p_array);
            b_result = cv_true;
        }
    }
    return b_result;
}

static void cv_options_node_cleanup_buf0(
    cv_options_node * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_buffer_cleanup(&(p_this->o_buffer));
}

static cv_bool cv_options_node_init(
    cv_options_node * p_this,
    cv_options_node_desc const * p_desc)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && p_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_options_node_init_node(p_this);
    if (cv_options_node_init_buffer(p_this, &p_desc->o_array)) {
        b_result = cv_true;
#if 0
        if (!b_result)
        {
            cv_options_node_cleanup_buf0(p_this);
        }
#endif
    }
    if (!b_result) {
        cv_options_node_cleanup_node(p_this);
        cv_debug_destruct_(g_class, p_this);
    }
    return b_result;
}

static void cv_options_node_cleanup(
    cv_options_node * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_options_node_cleanup_buf0(p_this);
    cv_options_node_cleanup_node(p_this);
    cv_debug_destruct_(g_class, p_this);
}

cv_options_node * cv_options_node_create(
    cv_options_node_desc const * p_desc)
{
    cv_options_node * p_this = cv_null_;
    cv_debug_assert_(p_desc, cv_debug_code_null_ptr);
    p_this = cv_options_pool_alloc();
    if (p_this) {
        if (cv_options_node_init(p_this, p_desc)) {
        } else {
            cv_debug_msg_(cv_debug_code_error);
            cv_options_pool_free(p_this);
            p_this = cv_null_;
        }
    } else {
        cv_debug_msg_(cv_debug_code_out_of_memory);
    }
    return p_this;
}

void cv_options_node_destroy(
    cv_options_node * p_this)
{
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_options_node_cleanup(p_this);
    cv_options_pool_free(p_this);
}

