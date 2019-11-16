/* See LICENSE for license details */

#include <cv_options_it.h>

#include <cv_options.h>

#include <cv_options_desc.h>

#include <cv_options_node_ptr.h>

#include <cv_options_node.h>

#include <cv_unused.h>

char cv_options_it_init(
    cv_options_it * p_this,
    cv_options const * p_options)
{
    char b_result = 0;
    if (p_this && p_options)
    {
        b_result = cv_node_it_init(&p_this->o_node_it, &p_options->o_list);
    }
    return b_result;
}

void cv_options_it_cleanup(
    cv_options_it * p_this)
{
    if (p_this)
    {
        cv_node_it_cleanup(&p_this->o_node_it);
    }
}

char cv_options_it_next(
    cv_options_it * p_this,
    cv_string const * * r_string)
{
    char b_result = 0;

    if (p_this && r_string)
    {
        cv_options_node_ptr o_ptr;
        if (cv_node_it_next(&p_this->o_node_it, &o_ptr.o_node_ptr))
        {
            *r_string = & o_ptr.pc_options_node->o_buf0.o_buf1.o_buf;
            b_result = 1;
        }
    }

    return b_result;
}

