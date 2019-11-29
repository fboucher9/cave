/* See LICENSE for license details */

#include <cv_test_print.h>

#include <cv_file_std.h>

#include <cv_array.h>

#include <cv_number_enc.h>

#include <cv_number_desc.h>

#include <cv_array.h>

#include <cv_string_it.h>

#include <cv_sizeof.h>

void cv_print_array(
    cv_array const * p_array)
{
    cv_file_std_print(
        p_array);
}

void cv_print_0(
    char const * p_array0,
    long i_array0_max_len)
{
    cv_file_std_print_0(
        p_array0,
        i_array0_max_len);
}

void cv_print_number(
    cv_number_desc const * p_desc)
{
    char c_buffer[64u];
    cv_array o_buffer = cv_array_null_;
    cv_array_init_vector(&o_buffer, c_buffer, cv_sizeof_(c_buffer));
    {
        cv_string_it o_string_it = cv_string_it_initializer_;
        cv_string_it_init(&o_string_it, &o_buffer);
        if (cv_number_status_done ==
            cv_number_enc_convert(p_desc, &o_string_it))
        {
            cv_array o_result = cv_array_null_;
            cv_array_init_range(&o_result, c_buffer,
                    o_string_it.o_array.o_min.pc_void);
                cv_file_std_print(&o_result);
            cv_array_cleanup(&o_result);
        }
        cv_string_it_cleanup(&o_string_it);
    }
    cv_array_cleanup(&o_buffer);
}

void cv_print_dec(
    long i_number)
{
    cv_number_desc o_desc = cv_number_desc_initializer_;
    o_desc.o_data.i_signed = i_number;
    o_desc.o_format.i_flags = 0;
    cv_print_number(&o_desc);
}

void cv_print_hex(
    unsigned long i_number)
{
    cv_number_desc o_desc = cv_number_desc_initializer_;
    o_desc.o_data.i_unsigned = i_number;
    o_desc.o_format.i_flags = cv_number_flag_unsigned
        | cv_number_flag_hexadecimal;
    cv_print_number(&o_desc);
}

void cv_print_nl(void)
{
    cv_file_std_print_nl();
}

/* end-of-file: cv_test_print.c */
