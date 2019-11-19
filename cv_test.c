/* See LICENSE for license details */

#include <cv_main.h>

#include <cv_options_desc.h>

#include <cv_options.h>

#include <cv_options_it.h>

#include <cv_debug.h>

#include <cv_string.h>

#include <cv_thread.h>

#include <cv_thread_desc.h>

#include <cv_heap.h>

#include <cv_null.h>

#include <cv_unused.h>

#include <stdio.h>

static void cv_test_job(
    void * p_context)
{
    cv_unused_(p_context);
    printf("thread says hello\n");
}

static char cv_test_func(
    cv_options const * p_options)
{
    {
        /* Test large allocation */
        void * const p_large = cv_heap_alloc(64 * 1024);
        if (p_large)
        {
            cv_heap_free(p_large);
        }
    }
    /* dump of cmd line options */
    {
        cv_options_it o_options_it;
        if (cv_options_it_init(
                &o_options_it,
                p_options))
        {
            cv_string const * p_cur;
            while (cv_options_it_next(&o_options_it, &p_cur))
            {
                printf("option = %s\n", p_cur->o_min.pc_char);
            }
            cv_options_it_cleanup(&o_options_it);
        }
    }
    cv_debug_msg_("dont panic");
    {
        cv_thread_desc o_desc;
        if (cv_thread_desc_init(&o_desc))
        {
            o_desc.p_func = & cv_test_job;
            o_desc.p_name0 = "job";
            {
                cv_thread * const p_thread = cv_thread_create(&o_desc);
                if (p_thread)
                {
                    cv_thread_destroy(p_thread);
                }
            }
            cv_thread_desc_cleanup(&o_desc);
        }
    }
    return 1;
}

int main(
    int argc,
    char const * const * argv)
{
    int i_result = 1;
    cv_options_desc o_options_desc = cv_options_desc_initializer_;
    if (cv_options_desc_init(&o_options_desc))
    {
        o_options_desc.p_args_min = argv;
        o_options_desc.p_args_max = argv + argc;
        if (cv_main_dispatch(&o_options_desc, &cv_test_func))
        {
            i_result = 0;
        }
        else
        {
        }
        cv_options_desc_cleanup(&o_options_desc);
    }
    return i_result;
}

