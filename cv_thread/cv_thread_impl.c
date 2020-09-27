/* See LICENSE for license details */

#include <cv_thread/cv_thread.h>
#include <cv_thread/cv_thread_ptr.h>
#include <cv_memory.h>
#include <cv_debug/cv_debug.h>
#include <cv_heap/cv_heap.h>
#include <cv_thread/cv_thread_plugin.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_algo/cv_unique.h>

cv_debug_decl_(g_class);

static cv_bool g_thread_loaded = cv_false;

static cv_thread_local_ cv_bool t_thread_self_initialized = cv_false;

static cv_thread_local_ cv_thread t_thread_self = { 0 };

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
    cv_thread_desc_ptr o_context_ptr = {0};
    o_context_ptr.p_void = p_void;

    cv_debug_assert_(g_thread_loaded, cv_debug_code_not_loaded);
    cv_debug_assert_( p_void, cv_debug_code_null_ptr);

    {
        cv_thread_desc const o_desc =
            *(o_context_ptr.pc_thread_desc);

        cv_thread_desc_cleanup(o_context_ptr.p_thread_desc);
        cv_heap_free(o_context_ptr.p_void);

        cv_debug_assert_( o_desc.o_callback.p_func,
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
        cv_memory_zero(p_this, sizeof(cv_thread));
        {
            static unsigned char const a_thread_desc_class[] = {
                't', 'h', 'r', 'e', 'a', 'd', '_', 'd', 'e', 's', 'c'
            };
            static cv_unique g_thread_desc_unique =
                cv_unique_initializer_(a_thread_desc_class);
            cv_thread_desc_ptr o_desc_ptr = {0};
            cv_unique_next(&g_thread_desc_unique);
            o_desc_ptr.p_void = cv_heap_alloc(sizeof(cv_thread_desc),
                &g_thread_desc_unique);
            if (o_desc_ptr.p_void) {
                cv_thread_desc_init(o_desc_ptr.p_thread_desc);
                *(o_desc_ptr.p_thread_desc) = *(p_thread_desc);
                {
                    int i_pthread_result = 0;
#if defined cv_have_pthread_
                    i_pthread_result = pthread_create(
                        &(p_this->o_handle),
                        0,
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
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    {
        /* check detach flag */
        int i_pthread_result = 0;
        void * p_result = 0;
#if defined cv_have_pthread_
        i_pthread_result = pthread_join(p_this->o_handle, &p_result);
#endif /* #if defined cv_have_pthread_ */
        (void)(p_result);
        if (0 == i_pthread_result) {
        } else {
            cv_debug_msg_(cv_debug_code_error);
        }
        cv_debug_destruct_(g_class, p_this);
    }
}

cv_thread const * cv_thread_self(void) {
    if (!t_thread_self_initialized) {
        t_thread_self_initialized = cv_true;
#if defined cv_have_pthread_
        t_thread_self.o_handle = pthread_self();
#else /* #if defined cv_have_pthread_ */
        t_thread_self.o_handle = 0;
#endif /* #if defined cv_have_pthread_ */
    }
    return &t_thread_self;
}

cv_bool cv_thread_equal(
    cv_thread const * p_thread_1,
    cv_thread const * p_thread_2) {
    cv_bool b_result = cv_false;
#if defined cv_have_pthread_
    b_result = (0 != pthread_equal(p_thread_1->o_handle,
            p_thread_2->o_handle));
#else /* #if defined cv_have_pthread_ */
    (void)p_thread_1;
    (void)p_thread_2;
    b_result = cv_false;
#endif /* #if defined cv_have_pthread_ */
    return b_result;
}

