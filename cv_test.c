/* See LICENSE for license details */

#include <cv_test.h>
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
#include <cv_array_tool.h>
#include <cv_memory.h>
#include <cv_file_test.h>
#include <cv_sizeof.h>
#include <cv_stack_test.h>
#include <cv_file.h>

static void cv_test_job(
    void * p_context)
{
    cv_print_0("thread says hello", 80);
    cv_print_nl();
    cv_unused_(p_context);
}

static void cv_test_heap_large(void)
{
    /* Test large allocation */
    void * const p_large = cv_heap_alloc(64 * 1024);
    if (p_large) {
        cv_heap_free(p_large);
    }
}

/* dump of cmd line options */
static void cv_test_dump_options(
    cv_options const * p_options)
{
    cv_options_it o_options_it = cv_options_it_initializer_;
    cv_options_it_init( &o_options_it, p_options);
    {
        cv_array o_cur;
        while (cv_options_it_next(&o_options_it, &o_cur)) {
            cv_print_0("option = [", 80);
            cv_print_array(&o_cur);
            cv_print_0("]", 80);
            cv_print_nl();
        }
    }
    cv_options_it_cleanup(&o_options_it);
}

static void cv_test_debug(void)
{
    cv_debug_msg_("dont panic");
}

static void cv_test_poll_stdin(void)
{
    static char g_buf[80u];
    cv_array o_string = cv_array_null_;
    cv_array_init_vector(&o_string, g_buf, cv_sizeof_(g_buf));
    {
        cv_file_poll o_poll_stdin = cv_file_poll_initializer_;
        cv_file const * p_std_in = cv_file_std_in();
        o_poll_stdin.p_file = p_std_in;
        o_poll_stdin.i_flags_in = cv_file_poll_flag_read;
        o_poll_stdin.i_flags_out = 0;
        if (cv_file_poll_dispatch(&o_poll_stdin,
                &o_poll_stdin + 1, cv_null_)) {
            long const i_file_read_result =
                cv_file_read(p_std_in, &o_string);
            cv_unused_(i_file_read_result);
        } else {
            cv_debug_msg_("poll error");
        }
    }
    cv_array_cleanup(&o_string);
}

static void cv_test_thread(void)
{
    cv_thread_desc o_desc;
    if (cv_thread_desc_init(&o_desc)) {
        o_desc.p_func = & cv_test_job;
        o_desc.p_name0 = "job";
        {
            cv_thread * const p_thread = cv_thread_create(&o_desc);
            if (p_thread) {
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
    cv_print_0("number = [", 80);
    cv_print_number(p_desc);
    cv_print_0("]", 80);
    cv_print_nl();
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
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_digits = 7;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_signed = 123;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_digits = 0;
    o_desc.o_format.i_width = 10;
    o_desc.o_format.i_precision = 2;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_signed = 123;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_digits = 0;
    o_desc.o_format.i_width = 10;
    o_desc.o_format.i_precision = 5;
    cv_test_number_step(&o_desc);
}

static void cv_test_stdin(void)
{
    cv_print_0("test stdin...", 80);
    cv_print_nl();

    {
        cv_bool b_continue = cv_true;
        while (b_continue) {
            cv_array o_string = cv_array_null_;
            unsigned char a_buf[1u];
            cv_array_init_vector(&o_string, a_buf, cv_sizeof_(a_buf));
            {
                cv_file const * p_std_in = cv_file_std_in();
                long const i_file_read_result =
                    cv_file_read(p_std_in,
                        &o_string);
                if (i_file_read_result > 0) {
                    cv_number_desc o_number_desc = cv_number_desc_initializer_;
                    o_number_desc.o_data.i_unsigned = a_buf[0u];
                    o_number_desc.o_format.i_flags = cv_number_flag_unsigned
                        | cv_number_flag_hexadecimal;
                    o_number_desc.o_format.i_digits = 2;
                    cv_print_0("0x", 80);
                    cv_print_number(&o_number_desc);
                    cv_print_nl();
                } else {
                    b_continue = cv_false;
                }
            }
            cv_array_cleanup(&o_string);
        }
    }

    cv_print_0("test stdin done.", 80);
    cv_print_nl();
}

static cv_bool cv_test_main_cb(
    cv_options const * p_options)
{
    cv_print_0("welcome.", 80);
    cv_print_nl();

    cv_test_dump_options(p_options);

    {
        cv_options_it o_options_it = cv_options_it_initializer_;
        cv_options_it_init(&o_options_it, p_options);
        {
            cv_array o_string = cv_array_null_;
            if (cv_options_it_next(&o_options_it, &o_string)) {
                if (cv_options_it_next(&o_options_it, &o_string)) {
                    static char const g_number_text[] = {
                        'n', 'u', 'm', 'b', 'e', 'r' };
                    static char const g_heap_large_text[] = {
                        'h', 'e', 'a', 'p', '.', 'l', 'a', 'r', 'g', 'e' };
                    static char const g_debug_text[] = {
                        'd', 'e', 'b', 'u', 'g' };
                    static char const g_thread_text[] = {
                        't', 'h', 'r', 'e', 'a', 'd' };
                    static char const g_stdin_text[] = {
                        's', 't', 'd', 'i', 'n' };
                    static char const g_file_text[] = {
                        'f', 'i', 'l', 'e' };
                    static char const g_stack_text[] = {
                        's', 't', 'a', 'c', 'k' };

                    static cv_array const g_number_array =
                        cv_array_text_initializer_(g_number_text);
                    static cv_array const g_heap_large_array =
                        cv_array_text_initializer_(g_heap_large_text);
                    static cv_array const g_debug_array =
                        cv_array_text_initializer_(g_debug_text);
                    static cv_array const g_thread_array =
                        cv_array_text_initializer_(g_thread_text);
                    static cv_array const g_stdin_array =
                        cv_array_text_initializer_(g_stdin_text);
                    static cv_array const g_file_array =
                        cv_array_text_initializer_(g_file_text);
                    static cv_array const g_stack_array =
                        cv_array_text_initializer_(g_stack_text);

                    if (cv_array_compare(&o_string, &g_number_array)) {
                        cv_test_number();
                    } else if (cv_array_compare(&o_string, &g_heap_large_array)) {
                        cv_test_heap_large();
                    } else if (cv_array_compare(&o_string, &g_debug_array)) {
                        cv_test_debug();
                    } else if (cv_array_compare(&o_string, &g_thread_array)) {
                        cv_test_thread();
                    } else if (cv_array_compare(&o_string, &g_stdin_array)) {
                        cv_test_stdin();
                    } else if (cv_array_compare(&o_string, &g_file_array)) {
                        cv_file_test();
                    } else if (cv_array_compare(&o_string, &g_stack_array)) {
                        cv_stack_test();
                    } else {
                        cv_print_0("invalid command", 80);
                        cv_print_nl();
                    }
                } else {
                    cv_print_0("missing command", 80);
                    cv_print_nl();
                }
            }
        }
        cv_options_it_cleanup(&o_options_it);
    }

    cv_print_0("goodbye.", 80);
    cv_print_nl();

    return cv_true;
}

int cv_test_main(
    int argc,
    char const * const * argv)
{
    int i_result = 1;
    {
        cv_options * p_options = cv_main_init(argc, argv);
        if (p_options) {
            if (cv_test_main_cb(p_options)) {
                i_result = 0;
            }
            cv_main_cleanup(p_options);
        }
    }
    return i_result;
}

