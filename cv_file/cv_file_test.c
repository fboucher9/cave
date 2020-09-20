/* See LICENSE for license details */

/*
 *  Module: cv_file_test.c
 *
 *  Description: Unit tests for cv_file module.
 */

#include <cv_file/cv_file_test.h>
#include <cv_file/cv_file.h>
#include <cv_file/cv_file_disk.h>
#include <cv_file/cv_file_disk_desc.h>
#include <cv_file/cv_file_print.h>
#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file_poll.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_it.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_misc/cv_cast.h>
#include <cv_test_print.h>
#include <cv_number/cv_number_desc.h>

/*
 *  Function: cv_file_test_dump_buffer()
 *
 *  Description: Dump result of read file.
 */

static void cv_file_test_dump_buffer(
    unsigned char const * a_read_buffer,
    cv_uptr i_read_result)
{
    cv_array o_read_result = {0};
    cv_array_init_vector(&o_read_result,
            a_read_buffer,
            i_read_result);
    {
        cv_array_it o_array_it = {0};
        cv_array_it_init(&o_array_it, &o_read_result);
        {
            unsigned char c_data = 0;
            while (cv_array_it_read_next_char(
                    &o_array_it,
                    &c_data)) {
                cv_print_char('0');
                cv_print_char('x');
                cv_print_hex(c_data);
                cv_print_nl();
            }
        }
        cv_array_it_cleanup(&o_array_it);
    }
    cv_array_cleanup(&o_read_result);
}

static void process_file_contents(
    cv_file_disk const * p_file_disk) {
    cv_bool b_continue = cv_true;
    while (b_continue) {
        unsigned char a_read_buffer[8u];
        cv_array o_read_buffer = {0};
        cv_array_init_vector(&o_read_buffer, a_read_buffer,
                sizeof(a_read_buffer));
        {
            cv_sptr const i_read_result = cv_file_read(
                &p_file_disk->o_file,
                &o_read_buffer);
            if (i_read_result > 0) {
                cv_uptr const i_buffer_len = cv_cast_(cv_uptr)(i_read_result);
                cv_file_test_dump_buffer( a_read_buffer, i_buffer_len);
            } else {
                b_continue = cv_false;
            }
        }
        cv_array_cleanup(&o_read_buffer);
    }
}

static cv_array const * get_input_bin_name(void) {
    static unsigned char const a_text[] = {
        'i', 'n', 'p', 'u', 't', '.', 'h', 'e', 'x' };
    static cv_array const g_text =
        cv_array_text_initializer_(a_text);
    return &g_text;
}

static cv_array const * get_input_fail_name(void) {
    static unsigned char const a_text[] = {
        'i', 'n', 'p', 'u', 't', '.', 'b', 'a', 'd' };
    static cv_array const g_text =
        cv_array_text_initializer_(a_text);
    return &g_text;
}

/*
 *
 */

static cv_bool cv_file_test_init_disk_read(cv_file_disk * p_file_disk,
    cv_array const * p_name) {
    cv_bool b_result = cv_false;
    cv_file_disk_desc o_desc = {0};
    cv_file_disk_desc_init(&o_desc);
    o_desc.p_name = p_name;
    o_desc.e_mode = cv_file_disk_mode_read;
    b_result = cv_file_disk_init(p_file_disk, &o_desc);
    cv_file_disk_desc_cleanup(&o_desc);
    return b_result;
}

/* */
static void cv_file_test_disk_read(void) {
    cv_file_disk o_file_disk = {0};
    if (cv_file_test_init_disk_read(&o_file_disk, get_input_bin_name())) {
        process_file_contents(&o_file_disk);
        cv_file_disk_cleanup(&o_file_disk);
    }
}

/* */
static void cv_file_test_disk_read_fail(void) {
    cv_file_disk o_file_disk = {0};
    cv_file_test_init_disk_read(&o_file_disk, get_input_fail_name());
}

static cv_array const * get_output_bin_name(void) {
    static unsigned char const a_text[] = {
        'o', 'u', 't', 'p', 'u', 't', '.', 'h', 'e', 'x' };
    static cv_array const g_text =
        cv_array_text_initializer_(a_text);
    return &g_text;
}

static cv_array const * get_output_body(void) {
    static unsigned char const a_text[] = {
        'h', 'e', 'l', 'l', 'o', ' ', 't', 'h', 'e', 'r', 'e', '!' };
    static cv_array const g_text =
        cv_array_text_initializer_(a_text);
    return &g_text;
}

static cv_array const * get_append_body(void) {
    static unsigned char const a_text[] = {
        'a', 'g', 'a', 'i', 'n' };
    static cv_array const g_text =
        cv_array_text_initializer_(a_text);
    return &g_text;
}

static void cv_file_test_disk_write(void) {
    cv_file_disk_desc o_desc = {0};
    cv_file_disk_desc_init(&o_desc);
    o_desc.p_name = get_output_bin_name();
    o_desc.e_mode = cv_file_disk_mode_write;
    {
        cv_file_disk o_file_disk = {0};
        if (cv_file_disk_init(&o_file_disk, &o_desc)) {
            cv_file_print_array(&o_file_disk.o_file, get_output_body());
            cv_file_print_nl(&o_file_disk.o_file);
            cv_file_disk_cleanup(&o_file_disk);
        }
    }
    cv_file_disk_desc_cleanup(&o_desc);
}

static void cv_file_test_disk_append(void) {
    cv_file_disk_desc o_desc = {0};
    cv_file_disk_desc_init(&o_desc);
    o_desc.p_name = get_output_bin_name();
    o_desc.e_mode = cv_file_disk_mode_append;
    {
        cv_file_disk o_file_disk = {0};
        if (cv_file_disk_init(&o_file_disk, &o_desc)) {
            cv_file_print_array(&o_file_disk.o_file, get_append_body());
            cv_file_print_nl(&o_file_disk.o_file);
            cv_file_disk_cleanup(&o_file_disk);
        }
    }
    cv_file_disk_desc_cleanup(&o_desc);
}

static cv_array const * get_line_buf(void) {
    static unsigned char a_line[80u];
    static cv_array const g_array =
        cv_array_text_initializer_(a_line);
    return &g_array;
}

/*
 *
 */

static void cv_file_test_stdin(void) {
    cv_file const * p_stdin = cv_file_std_in();
    cv_print_0("type something ...", 80);
    cv_print_nl();
    {
        long const i_read_result = cv_file_read(p_stdin,
            get_line_buf());
        (void)(i_read_result);
    }
}

/*
 *
 */

static cv_array const * get_hello_msg(void) {
    static unsigned char const a_text[] = {
        'h', 'e', 'l', 'l', 'o', '!', '\n' };
    static cv_array const g_array =
        cv_array_text_initializer_(a_text);
    return &g_array;
}

/*
 *
 */

static void cv_file_test_stdout(void) {
    cv_file const * p_stdout = cv_file_std_out();
    long const i_write_result = cv_file_write(p_stdout,
        get_hello_msg());
    (void)(i_write_result);
}

/*
 *
 */

static void cv_file_test_stderr(void) {
    cv_file const * p_stderr = cv_file_std_err();
    long const i_write_result = cv_file_write(p_stderr,
        get_hello_msg());
    (void)(i_write_result);
}

/*
 *
 */

static void cv_file_test_print(void) {
    cv_file const * p_stdout = cv_file_std_out();
    cv_file_print_char(p_stdout, '!');
    cv_file_print_array(p_stdout, get_hello_msg());
    {
        static unsigned char a_range[] = {
            'a', 'b', 'c' };
        cv_file_print_range(p_stdout, a_range, a_range + sizeof(a_range));
        cv_file_print_nl(p_stdout);
        cv_file_print_vector(p_stdout, a_range, sizeof(a_range));
        cv_file_print_nl(p_stdout);
    }
    cv_file_print_0(p_stdout, "abc", 10);
    cv_file_print_nl(p_stdout);
    {
        cv_number_desc o_number_desc = {0};
        o_number_desc.o_data.i_unsigned = 12345;
        o_number_desc.o_data.b_negative = 1;
        o_number_desc.o_format = *cv_number_format_dec();
        cv_file_print_number(p_stdout, &o_number_desc);
        cv_file_print_nl(p_stdout);
        cv_file_print_signed(p_stdout, -12345, cv_number_format_dec());
        cv_file_print_nl(p_stdout);
        cv_file_print_signed(p_stdout, 12345, cv_number_format_dec());
        cv_file_print_nl(p_stdout);
        cv_file_print_unsigned(p_stdout, 12345, cv_number_format_dec());
        cv_file_print_nl(p_stdout);
    }
}

/*
 *
 */

static void cv_file_test_poll(void) {
    cv_file_disk o_disk_read = {0};
    cv_file const * p_stdin = cv_file_std_in();
    cv_file const * p_stdout = cv_file_std_out();
    {
        cv_file_poll a_poll[1u] = {0};
        a_poll[0u].p_file = p_stdin;
        a_poll[0u].i_flags_in = cv_file_poll_flag_read;
        if (cv_file_poll_dispatch(a_poll, 1, 0)) {
        }
    }
    {
        if (cv_file_test_init_disk_read(&o_disk_read, get_input_bin_name())) {
            cv_file_poll a_poll[1u] = {0};
            a_poll[0u].p_file = &o_disk_read.o_file;
            a_poll[0u].i_flags_in = cv_file_poll_flag_read;
            if (cv_file_poll_dispatch(a_poll, 1, 0)) {
            }
            cv_file_disk_cleanup(&o_disk_read);
        }
    }
    {
        cv_file_poll a_poll[1u] = {0};
        a_poll[0u].p_file = p_stdout;
        a_poll[0u].i_flags_in = cv_file_poll_flag_write;
        if (cv_file_poll_dispatch(a_poll, 1, 0)) {
        }
    }
    {
        cv_file_poll a_poll[2u] = {0};
        a_poll[0u].p_file = p_stdin;
        a_poll[0u].i_flags_in = cv_file_poll_flag_read;
        a_poll[1u].p_file = p_stdout;
        a_poll[1u].i_flags_in = cv_file_poll_flag_write;
        if (cv_file_poll_dispatch(a_poll, 2, 0)) {
        }
    }
}

/*
 *
 */

void cv_file_test(void)
{
    /* Test stdin */
    cv_file_test_stdin();
    /* Test stdout */
    cv_file_test_stdout();
    /* Test stderr */
    cv_file_test_stderr();
    /* Test disk read */
    cv_file_test_disk_read();
    /* Test disk write */
    cv_file_test_disk_write();
    /* Test disk append */
    cv_file_test_disk_append();
    /* Test print */
    cv_file_test_print();
    /* Test poll */
    cv_file_test_poll();
    /* Test disk read failure */
    cv_file_test_disk_read_fail();
}

/* end-of-file: cv_file_test.c */
