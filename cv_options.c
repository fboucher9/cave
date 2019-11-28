/* See LICENSE for license details */

#include <cv_options.h>

#include <cv_options_desc.h>

#include <cv_options_node.h>

#include <cv_options_node_desc.h>

#include <cv_options_node_ptr.h>

#include <cv_options_plugin.h>

#include <cv_options_pool.h>

#include <cv_node_it.h>

#include <cv_heap.h>

#include <cv_null.h>

#include <cv_sizeof.h>

#include <cv_memory.h>

#include <cv_array.h>

#include <cv_array_it.h>

#include <cv_debug.h>

cv_bool cv_options_load(void)
{
    cv_bool b_result = cv_false;
    if (cv_options_pool_load())
    {
        b_result = cv_true;
    }
    return b_result;
}

void cv_options_unload(void)
{
    cv_options_pool_unload();
}

static void cv_options_cleanup_list(
    cv_options * p_this)
{
    if (p_this)
    {
        cv_node_it o_node_it;
        if (cv_node_it_init(&o_node_it, &p_this->o_list))
        {
            cv_options_node_ptr o_options_node_ptr;
            while (cv_node_it_first(&o_node_it,
                    &o_options_node_ptr.o_node_ptr))
            {
                cv_options_node_destroy(
                    o_options_node_ptr.p_options_node);
            }
            cv_node_it_cleanup(&o_node_it);
        }
    }
}

/* Cleanup instance of cv_options object.  Undo all that was initialized
during entire lifetime of object.  */
void cv_options_cleanup(
    cv_options * p_this)
{
    if (p_this)
    {
        cv_options_cleanup_list(p_this);
        cv_list_cleanup(&p_this->o_list);
        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
}

/*
 *      Initialize instance of cv_options object using provided descriptor
 *      structure.  All strings are copied, using heap allocations.
 */
cv_bool cv_options_init(
    cv_options * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        cv_debug_init_(p_this, cv_sizeof_(*p_this));
        if (cv_list_init(&p_this->o_list))
        {
            b_result = cv_true;
        }
        if (!b_result)
        {
            cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
        }
    }
    return b_result;
}

static cv_bool cv_options_setup_cb(
    cv_options * p_this,
    char const * p_arg0,
    long i_arg0_max_len)
{
    cv_bool b_result = cv_false;
    if (p_this && p_arg0)
    {
        cv_array o_string = cv_array_null_;
        if (cv_array_init_0(&o_string, p_arg0, i_arg0_max_len))
        {
            b_result = cv_options_add(p_this, &o_string);
            cv_array_cleanup(&o_string);
        }
    }
    return b_result;
}

cv_bool cv_options_setup(
    cv_options * p_this,
    cv_options_desc const * p_desc)
{
    cv_bool b_result = cv_false;
    if (p_this && p_desc)
    {
        cv_array_it o_array_it = cv_array_it_initializer_;
        if (cv_array_it_init(&o_array_it, &p_desc->o_array))
        {
            cv_array_ptr o_array_ptr = cv_ptr_null_;
            b_result = cv_true;
            while (b_result && cv_array_it_read_next_ptr(&o_array_it,
                    &o_array_ptr.pc_void))
            {
                char const * const p_arg0 = o_array_ptr.pc_char;
                b_result = cv_options_setup_cb(p_this, p_arg0, 0x7FFFFFFFL);
            }
            cv_array_it_cleanup(&o_array_it);
        }
    }
    return b_result;
}

cv_bool cv_options_add(
    cv_options * p_this,
    cv_array const * p_array)
{
    cv_bool b_result = cv_false;
    if (p_this && p_array)
    {
        cv_options_node * p_options_node = cv_null_;
        cv_options_node_desc o_options_node_desc =
            cv_options_node_desc_initializer_;
        o_options_node_desc.p_parent = &p_this->o_list;
        o_options_node_desc.p_array = p_array;
        p_options_node = cv_options_node_create(
            &o_options_node_desc);
        if (p_options_node)
        {
            b_result = cv_true;
        }
    }
    return b_result;
}

