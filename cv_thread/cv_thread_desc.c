/* See LICENSE for license details */

#include <cv_thread/cv_thread_desc.h>

#include <cv_memory.h>

#include <cv_debug.h>

#include <cv_misc/cv_sizeof.h>

#include <cv_misc/cv_null.h>

#include <cv_misc/cv_unused.h>

static void cv_thread_dummy_func(
    void * p_context)
{
    cv_unused_(p_context);
}

void cv_thread_desc_init(
    cv_thread_desc * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    p_this->o_callback.p_func = & cv_thread_dummy_func;
    p_this->o_callback.p_context = cv_null_;
    cv_array_init(&p_this->o_name);
}

void cv_thread_desc_cleanup(
    cv_thread_desc * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_array_cleanup(&p_this->o_name);
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}
