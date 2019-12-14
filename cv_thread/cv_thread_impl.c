/* See LICENSE for license details */

#include <cv_thread/cv_thread.h>
#include <cv_thread/cv_thread_ptr.h>
#include <cv_memory.h>
#include <cv_misc/cv_null.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_debug.h>
#include <cv_misc/cv_unused.h>
#include <cv_heap/cv_heap.h>
#include <cv_thread/cv_thread_plugin.h>

cv_debug_decl_(g_class);

static cv_bool g_thread_loaded = cv_false;

cv_bool cv_thread_load(void) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(!g_thread_loaded, cv_debug_code_already_loaded);
    g_thread_loaded = cv_true;
    b_result = cv_true;
    return b_result;
}

void cv_thread_unload(void) {
    cv_debug_assert_(g_thread_loaded, cv_debug_code_already_unloaded);
    g_thread_loaded = cv_false;
}

#if defined cv_have_pthread_
static void * cv_thread_start(
    void * p_void)
{
    cv_thread_desc_ptr o_context_ptr = cv_ptr_null_;
    o_context_ptr.p_void = p_void;

    cv_debug_assert_(g_thread_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_( !!p_void, cv_debug_code_null_ptr);

    {
        cv_thread_desc const o_desc =
            *(o_context_ptr.pc_thread_desc);

        cv_thread_desc_cleanup(o_context_ptr.p_thread_desc);
        cv_heap_free(o_context_ptr.p_void);

        cv_debug_assert_( !!o_desc.o_callback.p_func,
            cv_debug_code_null_ptr);

        (*(o_desc.o_callback.p_func))( o_desc.o_callback.p_context);
    }

    return p_void;
}
#endif /* #if defined cv_have_pthread_ */

cv_bool cv_thread_init(
    cv_thread * p_this,
    cv_thread_desc const * p_thread_desc)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(g_thread_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_( p_this && p_thread_desc, cv_debug_code_null_ptr);
    {
        cv_debug_construct_(g_class, p_this);
        cv_memory_zero(p_this, cv_sizeof_(cv_thread));
        {
            cv_thread_desc_ptr o_desc_ptr = cv_ptr_null_;
            o_desc_ptr.p_void = cv_heap_alloc(cv_sizeof_(cv_thread_desc));
            if (o_desc_ptr.p_void) {
                cv_thread_desc_init(o_desc_ptr.p_thread_desc);
                *(o_desc_ptr.p_thread_desc) = *(p_thread_desc);
                {
                    int i_pthread_result = 0;
#if defined cv_have_pthread_
                    i_pthread_result = pthread_create(
                        &(p_this->o_handle),
                        cv_null_,
                        & cv_thread_start,
                        o_desc_ptr.p_void);
#endif /* #if defined cv_have_pthread_ */
                    if (0 == i_pthread_result) {
                        b_result = cv_true;
                    } else {
                        cv_debug_msg_(cv_debug_code_error);
                    }
                }
                if (!b_result) {
                    cv_thread_desc_cleanup(o_desc_ptr.p_thread_desc);
                    cv_heap_free(o_desc_ptr.p_void);
                }
            }
        }
        if (!b_result) {
            cv_debug_destruct_(g_class, p_this);
        }
    }
    return b_result;
}

void cv_thread_cleanup(
    cv_thread * p_this)
{
    cv_debug_assert_(g_thread_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    {
        /* check detach flag */
        int i_pthread_result = 0;
        void * p_result = cv_null_;
#if defined cv_have_pthread_
        i_pthread_result = pthread_join(p_this->o_handle, &p_result);
#endif /* #if defined cv_have_pthread_ */
        cv_unused_(p_result);
        if (0 == i_pthread_result) {
        } else {
            cv_debug_msg_(cv_debug_code_error);
        }
        cv_debug_destruct_(g_class, p_this);
    }
}

