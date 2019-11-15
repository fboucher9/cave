/* See LICENSE for license details */

#include <cv_thread.h>

#include <cv_thread_impl.h>

#include <cv_heap.h>

#include <cv_memory.h>

#include <cv_null.h>

#include <cv_sizeof.h>

#include <cv_debug.h>

/*

Create instance of cv_thread object using options from given descriptor.

*/
cv_thread * cv_thread_create(
    cv_thread_desc const * p_thread_desc)
{
    cv_thread * p_result = cv_null_;
    if (p_thread_desc)
    {
        cv_thread * const p_this = cv_new_(cv_thread);
        if (p_this)
        {
            if (cv_thread_init(p_this, p_thread_desc))
            {
                p_result = p_this;
            }
            else
            {
                cv_debug_msg_("failed init");
                cv_delete_(p_this);
            }
        }
        else
        {
            cv_debug_msg_("out of memory");
        }
    }
    else
    {
        cv_debug_msg_("invalid param");
    }
    return p_result;
}

void cv_thread_destroy(
    cv_thread * p_this)
{
    cv_thread_cleanup(p_this);
    cv_delete_(p_this);
}

