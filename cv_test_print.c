/* See LICENSE for license details */

#include <cv_test_print.h>
#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file_print.h>
#include <cv_algo/cv_array.h>
#include <cv_number/cv_number_desc.h>
#include <cv_misc/cv_cast.h>

void cv_print_char( unsigned char i_value) {
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_char(p_std_out, i_value);
}

void cv_print_array( cv_array const * p_array) {
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_array( p_std_out, p_array);
}

void cv_print_vector( void const * p_buffer, cv_uptr i_buffer_len ) {
    cv_file const * p_std_out = cv_file_std_out();
    cv_array o_array = {0};
    cv_array_init_vector(&o_array, p_buffer, i_buffer_len);
    cv_file_print_array( p_std_out, &o_array);
    cv_array_cleanup(&o_array);
}

void cv_print_0( char const * p_array0, cv_uptr i_array0_max_len) {
    cv_file const * p_std_out = cv_file_std_out();
    cv_array o_array = {0};
    cv_array_init_0(&o_array, p_array0, i_array0_max_len);
    cv_file_print_array( p_std_out, &o_array);
    cv_array_cleanup(&o_array);
}

void cv_print_number( cv_number_desc const * p_desc) {
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_number(p_std_out, p_desc);
}

void cv_print_signed( long i_number, cv_number_format const * p_format) {
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_signed(p_std_out, i_number, p_format);
}

void cv_print_unsigned( unsigned long i_number,
    cv_number_format const * p_format) {
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_unsigned(p_std_out, i_number, p_format);
}

void cv_print_dec( long i_number) {
    cv_print_signed(i_number, cv_number_format_dec());
}

void cv_print_hex( unsigned long i_number) {
    cv_print_unsigned(i_number, cv_number_format_hex());
}

void cv_print_nl(void) {
    cv_file const * p_std_out = cv_file_std_out();
    cv_file_print_nl(p_std_out);
}

/* end-of-file: cv_test_print.c */
