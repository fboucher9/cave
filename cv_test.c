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

#include <cv_number_enc.h>

#include <cv_number_desc.h>

#include <cv_string_it.h>

static void cv_test_job(
    void * p_context)
{
    cv_file_std_out_write0("thread says hello\n");
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
        cv_string o_cur;
        while (cv_options_it_next(&o_options_it, &o_cur))
        {
            cv_file_std_out_write0("option = [");
            cv_file_std_out_write(&o_cur.o_array);
            cv_file_std_out_write0("]\n");
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
    cv_string o_string = cv_string_initializer_;
    if (cv_string_init(&o_string))
    {
        static char g_buf[80u];

        cv_file_poll o_poll_stdin;

        o_poll_stdin.p_file = &g_cv_file_std_in.o_file;
        o_poll_stdin.i_flags_in = cv_file_poll_flag_read;
        o_poll_stdin.i_flags_out = 0;

        cv_string_setup(&o_string, g_buf,
            g_buf + sizeof(g_buf));

        if (cv_file_poll_dispatch(&o_poll_stdin,
                &o_poll_stdin + 1, cv_null_))
        {
            long const i_file_read_result =
                cv_file_read(&g_cv_file_std_in.o_file, &o_string.o_array);
            cv_unused_(i_file_read_result);
        }
        else
        {
            cv_debug_msg_("poll error");
        }

        cv_string_cleanup(&o_string);
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
    char c_buffer[64u];
    cv_string o_buffer = cv_string_initializer_;
    if (cv_string_init(&o_buffer))
    {
        cv_string_setup(&o_buffer,
            c_buffer,
            c_buffer + sizeof(c_buffer));
        {
            cv_string_it o_string_it = cv_string_it_initializer_;
            if (cv_string_it_init(&o_string_it, &o_buffer.o_array))
            {
                if (cv_number_status_done == cv_number_enc_convert(p_desc, &o_string_it))
                {
                    cv_string o_result = cv_string_initializer_;
                    if (cv_string_init(&o_result))
                    {
                        cv_string_setup(&o_result,
                            c_buffer,
                            o_string_it.o_array.o_min.pc_void);
                        cv_file_std_out_write0("number = [");
                        cv_file_std_out_write(&o_result.o_array);
                        cv_file_std_out_write0("]\n");
                        cv_string_cleanup(&o_result);
                    }
                }
                cv_string_it_cleanup(&o_string_it);
            }
        }
        cv_string_cleanup(&o_buffer);
    }
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
