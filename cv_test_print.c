/* See LICENSE for license details */

#include <cv_test_print.h>

#include <cv_file_std.h>

#include <cv_file_print.h>

#include <cv_array.h>

#include <cv_number_desc.h>

void cv_print_array(
    cv_array const * p_array)
{
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_array( p_std_out, p_array);
}

void cv_print_0(
    char const * p_array0,
    long i_array0_max_len)
{
    cv_file const * p_std_out = cv_file_std_out();
    cv_array o_array = cv_array_null_;
    cv_array_init_0(&o_array, p_array0, i_array0_max_len);
    cv_file_print_array( p_std_out, &o_array);
    cv_array_cleanup(&o_array);
}

void cv_print_number(
    cv_number_desc const * p_desc)
{
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_number(p_std_out, p_desc);
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
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_nl(p_std_out);
}

/* end-of-file: cv_test_print.c */
