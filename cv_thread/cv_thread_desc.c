/* See LICENSE for license details */

#include <cv_thread/cv_thread_desc.h>

#include <cv_memory.h>

#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class);

static void cv_thread_dummy_func(
    void * p_context)
{
    (void)p_context;
}

void cv_thread_desc_init(
    cv_thread_desc * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    p_this->o_callback.p_func = & cv_thread_dummy_func;
    p_this->o_callback.p_context = 0;
    cv_array_init(&p_this->o_name);
}

void cv_thread_desc_cleanup(
    cv_thread_desc * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_array_cleanup(&p_this->o_name);
    cv_debug_destruct_(g_class, p_this);
}
