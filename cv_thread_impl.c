/* See LICENSE for license details */

#include <cv_thread_impl.h>

#include <cv_memory.h>

#include <cv_null.h>

#include <cv_sizeof.h>

#include <cv_unused.h>

typedef union cv_thread_start_ptr
{
    void * p_void;
    cv_thread * p_thread;
} cv_thread_start_ptr;

#if defined cv_have_pthread_
static void * cv_thread_start(
    void * p_void)
{
    cv_thread_start_ptr o_context_ptr;
    o_context_ptr.p_void = p_void;

    {
        cv_thread_desc const * const p_desc =
            &(o_context_ptr.p_thread->o_desc);

        if (p_desc->p_func)
        {
            (*(p_desc->p_func))(
                p_desc->p_context);
        }
    }

    return p_void;
}
#endif /* #if defined cv_have_pthread_ */

cv_bool cv_thread_init(
    cv_thread * p_this,
    cv_thread_desc const * p_thread_desc)
{
    cv_bool b_result = cv_false_;
    if (p_this && p_thread_desc)
    {
        cv_memory_zero(p_this, cv_sizeof_(cv_thread));
        p_this->o_desc = *(p_thread_desc);
        {
            int i_pthread_result = 0;
#if defined cv_have_pthread_
            i_pthread_result = pthread_create(
                &(p_this->u.o_handle),
                cv_null_,
                & cv_thread_start,
                p_this);
#endif /* #if defined cv_have_pthread_ */
            if (0 == i_pthread_result)
            {
                b_result = cv_true_;
            }
        }
    }
    return b_result;
}

void cv_thread_cleanup(
    cv_thread * p_this)
{
    if (p_this)
    {
        /* check detach flag */
        int i_pthread_result = 0;
        void * p_result = cv_null_;
#if defined cv_have_pthread_
        i_pthread_result = pthread_join(p_this->u.o_handle, &p_result);
#endif /* #if defined cv_have_pthread_ */
        cv_unused_(p_result);
        if (0 == i_pthread_result)
        {
        }
    }
}

