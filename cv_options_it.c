/* See LICENSE for license details */

#include <cv_options_it.h>

#include <cv_options.h>

#include <cv_options_desc.h>

#include <cv_options_node_ptr.h>

#include <cv_options_node.h>

#include <cv_array.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

void cv_options_it_init(
    cv_options_it * p_this,
    cv_options const * p_options)
{
    cv_debug_assert_( p_this && p_options, "null ptr");
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    cv_list_it_init(&p_this->o_list_it, &p_options->o_list);
}

void cv_options_it_cleanup(
    cv_options_it * p_this)
{
    cv_debug_assert_(!!p_this, "null ptr");
    cv_list_it_cleanup(&p_this->o_list_it);
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

cv_bool cv_options_it_next(
    cv_options_it * p_this,
    cv_array * r_string)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && r_string, "null ptr");
    {
        cv_options_node_ptr o_ptr = cv_ptr_null_;
        if (cv_list_it_next(&p_this->o_list_it, &o_ptr.o_list_ptr)) {
            *r_string = o_ptr.pc_options_node->o_buffer.o_array;
            b_result = cv_true;
        }
    }
    return b_result;
}

