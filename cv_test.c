/* See LICENSE for license details */

#include <cv_main.h>

#include <cv_options_desc.h>

#include <cv_options.h>

#include <cv_options_it.h>

#include <cv_debug.h>

#include <cv_array.h>

#include <cv_thread.h>

#include <cv_thread_desc.h>

#include <cv_heap.h>

#include <cv_file_std.h>

#include <cv_file_poll.h>

#include <cv_null.h>

#include <cv_unused.h>

#include <cv_number_enc.h>

#include <cv_number_desc.h>

#include <cv_string_it.h>

#include <cv_test_print.h>

static void cv_test_job(
    void * p_context)
{
    cv_print_array0("thread says hello\n", 80);
    cv_unused_(p_context);
}

static void cv_test_heap_large(void)
{
    /* Test large allocation */
    void * const p_large = cv_heap_alloc(64 * 1024);
    if (p_large)
    {
        cv_heap_free(p_large);
    }
}

/* dump of cmd line options */
static void cv_test_dump_options(
    cv_options const * p_options)
{
    cv_options_it o_options_it = cv_options_it_initializer_;
    if (cv_options_it_init(
            &o_options_it,
            p_options))
    {
        cv_array o_cur;
        while (cv_options_it_next(&o_options_it, &o_cur))
        {
            cv_print_array0("option = [", 80);
            cv_print_array(&o_cur);
            cv_print_array0("]\n", 80);
        }
        cv_options_it_cleanup(&o_options_it);
    }
}

static void cv_test_debug(void)
{
    cv_debug_msg_("dont panic");
}

static void cv_test_poll_stdin(void)
{
    cv_array o_string = cv_array_initializer_;
    if (cv_array_init(&o_string))
    {
        static char g_buf[80u];

        cv_file_poll o_poll_stdin;

        o_poll_stdin.p_file = &g_cv_file_std_in.o_file;
        o_poll_stdin.i_flags_in = cv_file_poll_flag_read;
        o_poll_stdin.i_flags_out = 0;

        cv_array_setup(&o_string, g_buf,
            g_buf + sizeof(g_buf));

        if (cv_file_poll_dispatch(&o_poll_stdin,
                &o_poll_stdin + 1, cv_null_))
        {
            long const i_file_read_result =
                cv_file_read(&g_cv_file_std_in.o_file, &o_string);
            cv_unused_(i_file_read_result);
        }
        else
        {
            cv_debug_msg_("poll error");
        }

        cv_array_cleanup(&o_string);
    }
}

static void cv_test_thread(void)
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
                cv_test_poll_stdin();
                cv_thread_destroy(p_thread);
            }
        }
        cv_thread_desc_cleanup(&o_desc);
    }
}

static void cv_test_number_step(
    cv_number_desc const * p_desc)
{
    cv_print_array0("number = [", 80);
    cv_print_number(p_desc);
    cv_print_array0("]\n", 80);
}

static void cv_test_number(void)
{
    cv_number_desc o_desc = cv_number_desc_initializer_;
    o_desc.o_data.i_signed = 12345;
    o_desc.o_format.i_flags = 0;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_signed = -12345;
    o_desc.o_format.i_flags = 0;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 0xabcd;
    o_desc.o_format.i_flags = cv_number_flag_unsigned | cv_number_flag_hexadecimal;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 0xabcd;
    o_desc.o_format.i_flags = cv_number_flag_unsigned | cv_number_flag_hexadecimal
        | cv_number_flag_upper;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_signed = 12345;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_signed = -12345;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_signed = 12345;
    o_desc.o_format.i_flags = cv_number_flag_left;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_signed = 12345;
    o_desc.o_format.i_flags = cv_number_flag_center;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_signed = 12345;
    o_desc.o_format.i_flags = cv_number_flag_zero;
    o_desc.o_format.i_digits = 7;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
}

static cv_bool cv_test_main_cb(
    cv_options const * p_options)
{
    cv_test_dump_options(p_options);

    cv_test_heap_large();

    cv_test_number();

    cv_test_debug();

    cv_test_thread();

    return cv_true;
}

static int cv_test_main(
    int argc,
    char const * const * argv)
{
    int i_result = 1;
    cv_options * p_options = cv_main_init(argc, argv);
    if (p_options)
    {
        if (cv_test_main_cb(p_options))
        {
            i_result = 0;
        }
        cv_main_cleanup(p_options);
    }
    return i_result;
}

#if defined cv_have_libc_

int main(
    int argc,
    char const * const * argv)
{
    return cv_test_main(argc, argv);
}

#else /* #if defined cv_have_libc_ */

#if defined __cplusplus
extern "C"
#endif /* #if defined __cplusplus */
void _start(void);

void _start(void)
{
    cv_test_main(0, cv_null_);
    __asm("movl $1,%eax;"
        "xorl %ebx,%ebx;"
        "int $0x80"
       );
}

#endif /* #if defined cv_have_libc_ */
