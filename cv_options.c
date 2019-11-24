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

#include <cv_string.h>

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
        cv_memory_zero(p_this, cv_sizeof_(cv_options));
        cv_list_init(&p_this->o_list);
        b_result = cv_true;
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
        cv_string o_string = cv_string_initializer_;
        if (cv_string_init(&o_string))
        {
            if (cv_string_setup0(&o_string, p_arg0, i_arg0_max_len))
            {
                b_result = cv_options_add(p_this, &o_string);
            }
            cv_string_cleanup(&o_string);
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
        char const * const * p_args_it = p_desc->o_array.o_min.ppc_char;
        b_result = cv_true;
        while (b_result && (p_args_it < p_desc->o_array.o_max.ppc_char))
        {
            char const * const p_arg0 = *p_args_it;
            b_result = cv_options_setup_cb(p_this, p_arg0, 0x7FFFFFFFL);
            p_args_it ++;
        }
    }
    return b_result;
}

cv_bool cv_options_add(
    cv_options * p_this,
    cv_string const * p_string)
{
    cv_bool b_result = cv_false;
    if (p_this && p_string)
    {
        cv_options_node * p_options_node = cv_null_;
        cv_options_node_desc o_options_node_desc =
            cv_options_node_desc_initializer_;
        o_options_node_desc.p_parent = &p_this->o_list;
        o_options_node_desc.p_string = p_string;
        p_options_node = cv_options_node_create(
            &o_options_node_desc);
        if (p_options_node)
        {
            b_result = cv_true;
        }
    }
    return b_result;
}

