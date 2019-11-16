/* See LICENSE for license details */

#include <cv_options.h>

#include <cv_options_desc.h>

#include <cv_options_node.h>

#include <cv_options_node_desc.h>

#include <cv_options_node_ptr.h>

#include <cv_heap.h>

#include <cv_null.h>

#include <cv_sizeof.h>

#include <cv_unused.h>

#include <cv_memory.h>

static void cv_options_cleanup_list(
    cv_options * p_this)
{
    if (p_this)
    {
        while (p_this->o_list.p_next != &p_this->o_list)
        {
            cv_options_node_ptr o_options_node_ptr;

            o_options_node_ptr.p_node =
                p_this->o_list.p_next;

            cv_options_node_destroy(
                o_options_node_ptr.p_options_node);
        }
    }
}

static char cv_options_init_list_cb(
    cv_options * p_this,
    char const * p_arg0)
{
    char b_result = 0;
    if (p_this && p_arg0)
    {
        cv_string o_string;
        if (cv_string_init0(&o_string, p_arg0))
        {
            b_result = cv_options_add(p_this, &o_string);

            cv_string_cleanup(&o_string);
        }
    }
    return b_result;
}

static char cv_options_init_list(
    cv_options * p_this)
{
    char b_result = 0;
    if (p_this)
    {
        char const * const * p_args_it = p_this->o_desc.p_args_min;
        b_result = 1;
        while (b_result && (p_args_it < p_this->o_desc.p_args_max))
        {
            char const * const p_arg0 = *p_args_it;
            b_result = cv_options_init_list_cb(p_this, p_arg0);
            p_args_it ++;
        }
        if (!b_result)
        {
            cv_options_cleanup_list(p_this);
        }
    }
    return b_result;
}

/*
 *      Cleanup instance of cv_options object.  Undo all that was initialized
 *      during entire lifetime of object.
 */
static void cv_options_cleanup(
    cv_options * p_this)
{
    if (p_this)
    {
        cv_options_cleanup_list(p_this);
    }
}

/*
 *      Initialize instance of cv_options object using provided descriptor
 *      structure.  All strings are copied, using heap allocations.
 */
static char cv_options_init(
    cv_options * p_this,
    cv_options_desc const * p_options_desc)
{
    char b_result = 0;
    if (p_this && p_options_desc)
    {
        cv_memory_zero(p_this, cv_sizeof_(cv_options));
        p_this->o_desc = *p_options_desc;
        cv_node_init(&p_this->o_list);
        if (cv_options_init_list(p_this))
        {
            b_result = 1;
        }
    }
    return b_result;
}

/*
 *      Create an instance of cv_options object.
 */
cv_options * cv_options_create(
    cv_options_desc const * p_options_desc)
{
    cv_options * p_result = cv_null_;

    /* Validate input parameters */
    if (p_options_desc)
    {
        /* Allocate memory for object */
        cv_options * const p_this = cv_new_(cv_options);

        /* Validate memory allocation */
        if (p_this)
        {
            /* Initialize object */
            if (cv_options_init(p_this, p_options_desc))
            {
                p_result = p_this;
            }
            else
            {
                /* Failed initialization, do cleanup */
                cv_delete_(p_this);
            }
        }
        else
        {
        }
    }
    else
    {
    }
    return p_result;
}

/*
 *      Destroy instance of cv_options object.  First do cleanup of object then
 *      free memory allocated for object.
 */
void cv_options_destroy(
    cv_options * p_this)
{
    /* Validate input parameters */
    if (p_this)
    {
        /* Cleanup of object */
        cv_options_cleanup(p_this);

        /* Free memory allocated for object */
        cv_delete_(p_this);
    }
}

char cv_options_add(
    cv_options * p_this,
    cv_string const * p_string)
{
    char b_result = 0;
    if (p_this && p_string)
    {
        cv_options_node * p_options_node;
        cv_options_node_desc o_options_node_desc;
        o_options_node_desc.p_parent = &p_this->o_list;
        o_options_node_desc.p_string = p_string;
        p_options_node = cv_options_node_create(
            &o_options_node_desc);
        if (p_options_node)
        {
            b_result = 1;
        }
    }
    return b_result;
}

