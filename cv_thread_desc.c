/* See LICENSE for license details */

#include <cv_thread_desc.h>

#include <cv_memory.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

#include <cv_null.h>

#include <cv_unused.h>

static void cv_thread_dummy_func(
    void * p_context)
{
    cv_unused_(p_context);
}

char cv_thread_desc_init(
    cv_thread_desc * p_this)
{
    cv_memory_zero(
        p_this,
        cv_sizeof_(cv_thread_desc));
    p_this->p_func = & cv_thread_dummy_func;
    p_this->p_context = cv_null_;
    p_this->p_name0 = cv_null_;
    return 1;
}

void cv_thread_desc_cleanup(
    cv_thread_desc * p_this)
{
    cv_unused_(p_this);
}
