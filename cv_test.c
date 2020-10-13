/* See LICENSE for license details */

#include <cv_test.h>
#include <cv_main.h>
#include <cv_options/cv_options_desc.h>
#include <cv_options/cv_options.h>
#include <cv_options/cv_options_it.h>
#include <cv_debug/cv_debug.h>
#include <cv_algo/cv_array.h>
#include <cv_thread/cv_thread.h>
#include <cv_thread/cv_thread_desc.h>
#include <cv_heap/cv_heap.h>
#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file_poll.h>
#include <cv_number/cv_number_enc.h>
#include <cv_number/cv_number_desc.h>
#include <cv_test_print.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_memory.h>
#include <cv_file/cv_file_test.h>
#include <cv_algo/cv_stack_test.h>
#include <cv_file/cv_file.h>
#include <cv_misc/cv_convert_test.h>
#include <cv_clock/cv_clock_test.h>
#include <cv_trace/cv_trace_test.h>
#include <cv_algo/cv_callstack.h>
#include <cv_number/cv_number_dec.h>
#include <cv_algo/cv_array_it.h>
#include <cv_number/cv_number_scan.h>
#include <cv_number/cv_number_test.h>
#include <cv_heap/cv_heap_test.h>
#include <cv_random/cv_random_test.h>
#include <cv_algo/cv_crc32_test.h>
#include <cv_json/cv_json_test.h>
#include <cv_unicode/cv_unicode_test.h>

static void cv_test_job(
    void * p_context)
{
    {
        static unsigned char const a_text[] = {
            't', 'h', 'r', 'e', 'a', 'd', ' ', 's',
            'a', 'y', 's', ' ', 'h', 'e', 'l', 'l',
            'o' };
        cv_print_vector(a_text, sizeof(a_text));
    }
    cv_print_nl();
    (void)(p_context);
}

static void cv_test_heap_large(void)
{
    /* Test large allocation */
    void * const p_large = cv_heap_alloc(64 * 1024, "test_heap_large", 0);
    if (p_large) {
        cv_heap_free(p_large);
    }
}

/* dump of cmd line options */
static void cv_test_dump_options(
    cv_options const * p_options)
{
    cv_options_it o_options_it = {0};
    cv_options_it_init( &o_options_it, p_options);
    {
        cv_array o_cur;
        while (cv_options_it_next(&o_options_it, &o_cur)) {
            {
                static unsigned char const a_text[] = {
                    'o', 'p', 't', 'i', 'o', 'n', ' ', '=', ' ', '[' };
                cv_print_vector(a_text, sizeof(a_text));
            }
            cv_print_array(&o_cur);
            cv_print_char(']');
            cv_print_nl();
        }
    }
    cv_options_it_cleanup(&o_options_it);
}

static void cv_test_debug(void)
{
    cv_debug_msg_(cv_debug_code_dont_panic);
}

static void cv_test_poll_stdin(void)
{
    static char g_buf[80u];
    cv_array o_string = {0};
    cv_array_init_vector(&o_string, g_buf, sizeof(g_buf));
    {
        cv_file_poll o_poll_stdin = {0};
        cv_file const * p_std_in = cv_file_std_in();
        o_poll_stdin.p_file = p_std_in;
        o_poll_stdin.i_flags_in = cv_file_poll_flag_read;
        o_poll_stdin.i_flags_out = 0;
        if (cv_file_poll_dispatch(&o_poll_stdin,
                1, 0)) {
            long const i_file_read_result =
                cv_file_read(p_std_in, &o_string);
            (void)(i_file_read_result);
        } else {
            cv_debug_msg_(cv_debug_code_error);
        }
    }
    cv_array_cleanup(&o_string);
}

static void cv_test_thread(void)
{
    cv_thread_desc o_desc = {0};
    cv_thread_desc_init(&o_desc);
    {
        static unsigned char const a_thread_name[] = {
            'j', 'o', 'b' };
        static cv_array const g_thread_name =
            cv_array_text_initializer_(a_thread_name);
        o_desc.o_callback.p_func = & cv_test_job;
        o_desc.o_name = g_thread_name;
        {
            cv_thread o_thread = {0};
            if (cv_thread_init(&o_thread, &o_desc)) {
                cv_test_poll_stdin();
                cv_thread_cleanup(&o_thread);
            }
        }
    }
    cv_thread_desc_cleanup(&o_desc);
}

#if 0
static void cv_test_number_step(
    cv_number_desc const * p_desc)
{
    {
        static unsigned char const a_text[] = {
            'n', 'u', 'm', 'b', 'e', 'r', ' ', '[' };
        cv_print_vector(a_text, sizeof(a_text));
    }
    cv_print_number(p_desc);
    cv_print_char(']');
    cv_print_nl();
}
#endif

#if 0
static void cv_test_number(void)
{
    cv_number_desc o_desc = {0};
    o_desc.o_format.i_base = 10;
    o_desc.o_data.i_unsigned = 12345;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = 0;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 12345;
    o_desc.o_data.b_negative = 1;
    o_desc.o_format.i_flags = 0;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 0xabcd;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_base = 16;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 0xabcd;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = cv_number_flag_upper;
    o_desc.o_format.i_base = 16;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 0xabcd;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = cv_number_flag_prefix;
    o_desc.o_format.i_base = 16;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 0xabcd;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = cv_number_flag_prefix | cv_number_flag_upper;
    o_desc.o_format.i_base = 16;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 12345;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_base = 10;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 12345;
    o_desc.o_data.b_negative = 1;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_base = 10;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 12345;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = cv_number_flag_left;
    o_desc.o_format.i_base = 10;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 12345;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = cv_number_flag_center;
    o_desc.o_format.i_base = 10;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 12345;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_base = 10;
    o_desc.o_format.i_digits = 7;
    o_desc.o_format.i_width = 10;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 123;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_base = 10;
    o_desc.o_format.i_digits = 0;
    o_desc.o_format.i_width = 10;
    o_desc.o_format.i_precision = 2;
    cv_test_number_step(&o_desc);
    o_desc.o_data.i_unsigned = 123;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_base = 10;
    o_desc.o_format.i_digits = 0;
    o_desc.o_format.i_width = 10;
    o_desc.o_format.i_precision = 5;
    cv_test_number_step(&o_desc);
}
#endif

/*
 *
 */

static void cv_test_number_dec(
    cv_options_it * p_options_it,
    unsigned int i_base) {
    cv_array o_string = {0};
    while (cv_options_it_next(p_options_it, &o_string)) {
        cv_number_dec o_number_dec = {0};
        cv_array_it o_string_it = {0};
        cv_array_it_init(&o_string_it, &o_string);
        cv_number_dec_init(&o_number_dec, i_base);
        while (cv_number_status_continue == cv_number_dec_write(&o_number_dec,
                &o_string_it)) {
        }
        {
            cv_number_desc o_desc = {0};
            if (cv_number_dec_read(&o_number_dec, &o_desc)) {
                cv_print_char('[');
                cv_print_number(&o_desc);
                cv_print_char(']');
            }
        }
        cv_print_nl();
        cv_number_dec_cleanup(&o_number_dec);
        cv_array_it_cleanup(&o_string_it);
    }
}

static void cv_test_stdin(void)
{
    {
        static unsigned char const a_text[] = {
            't', 'e', 's', 't', ' ', 's', 't', 'd', 'i', 'n',
            '.', '.', '.' };
        cv_print_vector(a_text, sizeof(a_text));
    }
    cv_print_nl();

    {
        cv_bool b_continue = cv_true;
        while (b_continue) {
            cv_array o_string = {0};
            unsigned char a_buf[1u];
            cv_array_init_vector(&o_string, a_buf, sizeof(a_buf));
            {
                cv_file const * p_std_in = cv_file_std_in();
                long const i_file_read_result =
                    cv_file_read(p_std_in,
                        &o_string);
                if (i_file_read_result > 0) {
                    {
                        static unsigned char const a_text[] = {
                            '0', 'x'
                        };
                        cv_print_vector(a_text, sizeof(a_text));
                    }
                    cv_print_unsigned(a_buf[0u], cv_number_format_hex2());
                    cv_print_nl();
                } else {
                    b_continue = cv_false;
                }
            }
            cv_array_cleanup(&o_string);
        }
    }

    {
        static unsigned char const a_text[] = {
            't', 'e', 's', 't', ' ', 's', 't', 'd', 'i', 'n',
            ' ', 'd', 'o', 'n', 'e', '.' };
        cv_print_vector(a_text, sizeof(a_text));
    }
    cv_print_nl();
}

static void cv_test_hello(void) {
    {
        /* welcome. */
        static unsigned char const a_text[] = {
            'h', 'e', 'l', 'l', 'o', '!' };
        cv_print_vector(a_text, sizeof(a_text));
        cv_print_nl();
    }
}

static void cv_test_leak1(void) {
    cv_debug_decl_(g_class, "leak1", sizeof(int));
    int i = 0;
    cv_debug_construct_(g_class, &i);
    (void)(i);
}

static void cv_test_leak2(void) {
    cv_debug_decl_(g_class, "leak2", sizeof(int));
    int i = 0;
    cv_debug_destruct_(g_class, &i);
    (void)(i);
}

static void cv_test_leak3(void) {
#if defined cv_have_callstack_
    unsigned long n = cv_callstack_enter("leak3");
#endif
    cv_heap_alloc(123, "test_leak3", 0);
#if defined cv_have_callstack_
    cv_callstack_leave(n);
#endif
}

static cv_bool cv_test_main_cb(
    cv_options const * p_options)
{
    cv_options_it o_options_it = {0};
    cv_options_it_init(&o_options_it, p_options);
    {
        cv_array o_string = {0};
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
                static char const g_convert_text[] = {
                    'c', 'o', 'n', 'v', 'e', 'r', 't' };
                static char const g_clock_text[] = {
                    'c', 'l', 'o', 'c', 'k' };
                static char const g_hello_text[] = {
                    'h', 'e', 'l', 'l', 'o' };
                static char const g_leak1_text[] = {
                    'l', 'e', 'a', 'k', '1' };
                static char const g_leak2_text[] = {
                    'l', 'e', 'a', 'k', '2' };
                static char const g_leak3_text[] = {
                    'l', 'e', 'a', 'k', '3' };
                static char const g_trace_text[] = {
                    't', 'r', 'a', 'c', 'e' };
                static char const g_ndec_text[] = {
                    'n', 'd', 'e', 'c' };
                static char const g_nhex_text[] = {
                    'n', 'h', 'e', 'x' };
                static char const g_heap_text[] = {
                    'h', 'e', 'a', 'p' };
                static char const g_random_text[] = {
                    'r', 'a', 'n', 'd', 'o', 'm' };
                static char const g_crc32_text[] = {
                    'c', 'r', 'c', '3', '2' };
                static char const g_json_text[] = {
                    'j', 's', 'o', 'n' };
                static char const g_unicode_text[] = {
                    'u', 'n', 'i', 'c', 'o', 'd', 'e' };

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
                static cv_array const g_convert_array =
                    cv_array_text_initializer_(g_convert_text);
                static cv_array const g_clock_array =
                    cv_array_text_initializer_(g_clock_text);
                static cv_array const g_hello_array =
                    cv_array_text_initializer_(g_hello_text);
                static cv_array const g_leak1_array =
                    cv_array_text_initializer_(g_leak1_text);
                static cv_array const g_leak2_array =
                    cv_array_text_initializer_(g_leak2_text);
                static cv_array const g_leak3_array =
                    cv_array_text_initializer_(g_leak3_text);
                static cv_array const g_trace_array =
                    cv_array_text_initializer_(g_trace_text);
                static cv_array const g_ndec_array =
                    cv_array_text_initializer_(g_ndec_text);
                static cv_array const g_nhex_array =
                    cv_array_text_initializer_(g_nhex_text);
                static cv_array const g_heap_array =
                    cv_array_text_initializer_(g_heap_text);
                static cv_array const g_random_array =
                    cv_array_text_initializer_(g_random_text);
                static cv_array const g_crc32_array =
                    cv_array_text_initializer_(g_crc32_text);
                static cv_array const g_json_array =
                    cv_array_text_initializer_(g_json_text);
                static cv_array const g_unicode_array =
                    cv_array_text_initializer_(g_unicode_text);

                if (cv_array_compare(&o_string, &g_number_array)) {
#if 0
                    cv_test_number();
#endif
                    cv_number_test();
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
                } else if (cv_array_compare(&o_string, &g_convert_array)) {
                    cv_convert_test();
                } else if (cv_array_compare(&o_string, &g_clock_array)) {
                    cv_clock_test();
                } else if (cv_array_compare(&o_string, &g_hello_array)) {
                    cv_test_hello();
                } else if (cv_array_compare(&o_string, &g_leak1_array)) {
                    cv_test_leak1();
                } else if (cv_array_compare(&o_string, &g_leak2_array)) {
                    cv_test_leak2();
                } else if (cv_array_compare(&o_string, &g_leak3_array)) {
                    cv_test_leak3();
                } else if (cv_array_compare(&o_string, &g_trace_array)) {
                    cv_trace_test();
                } else if (cv_array_compare(&o_string, &g_ndec_array)) {
                    cv_test_number_dec(&o_options_it, 10);
                } else if (cv_array_compare(&o_string, &g_nhex_array)) {
                    cv_test_number_dec(&o_options_it, 16);
                } else if (cv_array_compare(&o_string, &g_heap_array)) {
                    cv_heap_test(&o_options_it);
                } else if (cv_array_compare(&o_string, &g_random_array)) {
                    cv_random_test(&o_options_it);
                } else if (cv_array_compare(&o_string, &g_crc32_array)) {
                    cv_crc32_test();
                } else if (cv_array_compare(&o_string, &g_json_array)) {
                    cv_json_test(&o_options_it);
                } else if (cv_array_compare(&o_string, &g_unicode_array)) {
                    cv_unicode_test();
                } else {
                    /* invalid command */
                    static unsigned char const a_text[] = {
                        'i', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
                        'c', 'o', 'm', 'm', 'a', 'n', 'd' };
                    cv_print_vector(a_text, sizeof(a_text));
                    cv_print_nl();
                    cv_test_dump_options(p_options);
                }
            } else {
                /* missing command */
                static unsigned char const a_text[] = {
                    'm', 'i', 's', 's', 'i', 'n', 'g', ' ',
                    'c', 'o', 'm', 'm', 'a', 'n', 'd' };
                cv_print_vector(a_text, sizeof(a_text));
                cv_print_nl();
            }
        }
    }
    cv_options_it_cleanup(&o_options_it);
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

