/* See LICENSE for license details */

/*
 *  Module: cv_file_test.c
 *
 *  Description: Unit tests for cv_file module.
 */

#include <cv_file_test.h>

#include <cv_file.h>

#include <cv_file_disk.h>

#include <cv_file_disk_desc.h>

#include <cv_array.h>

#include <cv_array_it.h>

#include <cv_array_tool.h>

#include <cv_sizeof.h>

#include <cv_test_print.h>

/*
 *  Function: cv_file_test_dump_buffer()
 *
 *  Description: Dump result of read file.
 */

static void cv_file_test_dump_buffer(
    unsigned char const * a_read_buffer,
    long i_read_result)
{
    cv_array o_read_result = cv_array_null_;
    cv_array_init_vector(&o_read_result,
            a_read_buffer,
            i_read_result);
    {
        cv_array_it o_array_it = cv_array_it_initializer_;
        cv_array_it_init(&o_array_it, &o_read_result);
        {
            unsigned char c_data = 0;
            while (cv_array_it_read_next_char(
                    &o_array_it,
                    &c_data)) {
                cv_print_0("0x", 80);
                cv_print_hex(c_data);
                cv_print_nl();
            }
        }
        cv_array_it_cleanup(&o_array_it);
    }
    cv_array_cleanup(&o_read_result);
}

/* */
static void cv_file_test_disk_read(void)
{
    cv_file_disk_desc o_desc = cv_file_disk_desc_initializer_;
    cv_file_disk_desc_init(&o_desc);
    {
        static unsigned char const g_ref_input_bin_name[] = {
            'i',
            'n',
            'p',
            'u',
            't',
            '.',
            'h',
            'e',
            'x'
        };
        static cv_array const g_ref_input_bin_array =
            cv_array_text_initializer_(g_ref_input_bin_name);

        o_desc.o_name = g_ref_input_bin_array;
        o_desc.i_flags = cv_file_disk_flag_read;

        {
            cv_file_disk o_file_disk = cv_file_disk_initializer_;
            if (cv_file_disk_init(&o_file_disk, &o_desc)) {
                cv_bool b_continue = cv_true;
                while (b_continue) {
                    unsigned char a_read_buffer[8u];
                    cv_array o_read_buffer = cv_array_null_;
                    cv_array_init_vector(&o_read_buffer, a_read_buffer,
                            cv_sizeof_(a_read_buffer));
                    {
                        long const i_read_result = cv_file_read(
                            &o_file_disk.o_file,
                            &o_read_buffer);
                        if (i_read_result > 0) {
                            cv_file_test_dump_buffer(
                                a_read_buffer,
                                i_read_result);
                        } else {
                            b_continue = cv_false;
                        }
                    }
                    cv_array_cleanup(&o_read_buffer);
                }
                cv_file_disk_cleanup(&o_file_disk);
            }
        }
    }
    cv_file_disk_desc_cleanup(&o_desc);
}

/*

*/
void cv_file_test(void)
{
    /* Test stdin */
    /* Test stdout */
    /* Test stderr */
    /* Test disk read */
    cv_file_test_disk_read();
    /* Test disk write */
    /* Test disk append */
}

/* end-of-file: cv_file_test.c */
