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

#include <cv_file_std.h>

#include <cv_file_poll.h>

#include <cv_null.h>

#include <cv_unused.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

static void cv_test_job(
    void * p_context)
{
    static char const g_msg[] = "thread says hello\n";
    cv_file_std const * p_stdout = cv_file_std_out();
    cv_string o_string = cv_string_initializer_;
    o_string.o_min.pc_char = g_msg;
    o_string.o_max.pc_char = g_msg + sizeof(g_msg) - 1;
    cv_file_write(&p_stdout->o_file, &o_string);
    cv_unused_(p_context);
}

static cv_bool cv_test_func(
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
        cv_options_it o_options_it = cv_options_it_initializer_;
        if (cv_options_it_init(
                &o_options_it,
                p_options))
        {
            cv_string const * p_cur;
            while (cv_options_it_next(&o_options_it, &p_cur))
            {
#if defined cv_have_libc_
                printf("option = %s\n", p_cur->o_min.pc_char);
#endif /* #if defined cv_have_libc_ */
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
                    {
                        cv_file_std const * p_stdin = cv_file_std_in();
                        cv_string o_string = cv_string_initializer_;
                        if (cv_string_init(&o_string))
                        {
                            static char g_buf[80u];

                            cv_file_poll o_poll_stdin;

                            o_poll_stdin.p_file = &p_stdin->o_file;
                            o_poll_stdin.i_flags_in = cv_file_poll_flag_read;
                            o_poll_stdin.i_flags_out = 0;

                            cv_string_setup(&o_string, g_buf,
                                g_buf + sizeof(g_buf));

                            if (cv_file_poll_dispatch(&o_poll_stdin,
                                    &o_poll_stdin + 1, cv_null_))
                            {
                                long const i_file_read_result =
                                    cv_file_read(&p_stdin->o_file, &o_string);
                                cv_unused_(i_file_read_result);
                            }
                            else
                            {
#if defined cv_have_libc_
                                printf("poll err\n");
#endif /* #if defined cv_have_libc_ */
                            }

                            cv_string_cleanup(&o_string);
                        }
                    }
                    cv_thread_destroy(p_thread);
                }
            }
            cv_thread_desc_cleanup(&o_desc);
        }
    }
    return cv_true_;
}

#if defined cv_have_libc_
int main(
    int argc,
    char const * const * argv)
#else /* #if defined cv_have_libc_ */

#if defined __cplusplus
extern "C"
#endif /* #if defined __cplusplus */
void _start(void);

void _start(void)
#endif /* #if defined cv_have_libc_ */
{
    int i_result = 1;
#if ! defined cv_have_libc_
    int argc = 0;
    char const * const * argv = cv_null_;
#endif
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
#if defined cv_have_libc_
    return i_result;
#else /* #if defined cv_have_libc_ */
    cv_unused_(i_result);
    __asm("movl $1,%eax;"
        "xorl %ebx,%ebx;"
        "int $0x80"
       );
#endif /* #if defined cv_have_libc_ */
}

