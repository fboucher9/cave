/* See LICENSE for license details */

#include <cv_thread.h>

#include <cv_thread_impl.h>

#include <cv_thread_ptr.h>

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
    cv_debug_assert_(
        !!p_thread_desc,
        "invalid param");
    {
        cv_thread_ptr o_thread_ptr = cv_ptr_null_;
        o_thread_ptr.p_void = cv_heap_alloc(cv_sizeof_(cv_thread));
        if (o_thread_ptr.p_void)
        {
            if (cv_thread_init(o_thread_ptr.p_thread, p_thread_desc))
            {
                p_result = o_thread_ptr.p_thread;
            }
            else
            {
                cv_debug_msg_("failed init");
                cv_heap_free(o_thread_ptr.p_void);
            }
        }
        else
        {
            cv_debug_msg_("out of memory");
        }
    }
    return p_result;
}

void cv_thread_destroy(
    cv_thread * p_this)
{
    cv_thread_cleanup(p_this);
    cv_heap_free(p_this);
}

