/* See LICENSE for license details */

/*
 *  Module: cv_file_print.h
 *
 *  Description: Helper functions to print data to a file descriptor.
 */

#include <cv_file/cv_file_print.h>
#include <cv_file/cv_file.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_debug/cv_debug.h>
#include <cv_number/cv_number_print.h>
#include <cv_number/cv_number_desc.h>
#include <cv_misc/cv_limits.h>

/*
 *
 */

void cv_file_print_char( cv_file const * p_file,
    unsigned char i_value) {
    cv_array o_array = cv_array_null_;
    cv_array_init_vector(&o_array, &i_value, 1);
    cv_file_write(
        p_file,
        & o_array);
    cv_array_cleanup(&o_array);
}

/*
 *
 */

void cv_file_print_array( cv_file const * p_file,
    cv_array const * p_array) {
    cv_bool b_result = cv_true;
    cv_array o_array_it = cv_array_null_;
    cv_debug_assert_(p_file && p_array, cv_debug_code_null_ptr);
    cv_array_init_ref(&o_array_it, p_array);
    while (b_result &&
        (o_array_it.o_min.pc_char != o_array_it.o_max.pc_char)) {
        cv_sptr const i_write_result = cv_file_write(
            p_file,
            & o_array_it);
        b_result = cv_false;
        if (i_write_result > 0) {
            o_array_it.o_min.pc_char += i_write_result;
            b_result = cv_true;
        }
    }
    cv_array_cleanup(&o_array_it);
}

/*
 *
 */

void cv_file_print_range( cv_file const * p_file,
    void const * p_range_min, void const * p_range_max) {
    cv_array o_array = cv_array_null_;
    cv_array_init_range(&o_array, p_range_min, p_range_max);
    cv_file_print_array( p_file, &o_array);
    cv_array_cleanup(&o_array);
}

/*
 *
 */

void cv_file_print_vector( cv_file const * p_file,
    void const * p_buffer, cv_uptr i_buffer_len) {
    cv_array o_array = cv_array_null_;
    cv_array_init_vector(&o_array, p_buffer, i_buffer_len);
    cv_file_print_array( p_file, &o_array);
    cv_array_cleanup(&o_array);
}

/*
 *
 */

void cv_file_print_0( cv_file const * p_file,
    char const * p_buffer, cv_uptr i_max_len) {
    cv_array o_array = cv_array_null_;
    cv_array_init_0(&o_array, p_buffer, i_max_len);
    cv_file_print_array( p_file, &o_array);
    cv_array_cleanup(&o_array);
}

/*
 *
 */

void cv_file_print_number( cv_file const * p_file,
    cv_number_desc const * p_desc) {
    char c_buffer[64u];
    cv_debug_assert_(p_file && p_desc, cv_debug_code_null_ptr);
    {
        cv_array o_array = cv_array_null_;
        cv_array_init_vector(&o_array, c_buffer, sizeof(c_buffer));
        {
            cv_uptr const i_buffer_len = cv_number_print(p_desc, &o_array);
            if ((i_buffer_len > 0) &&
                (i_buffer_len <= sizeof(c_buffer))) {
                cv_file_print_vector(p_file, c_buffer, i_buffer_len);
            }
        }
        cv_array_cleanup(&o_array);
    }
}

/*
 *
 */

void cv_file_print_signed( cv_file const * p_file,
    long i_number,
    cv_number_format const * p_format) {
    cv_number_desc o_desc = cv_number_desc_initializer_;
    if (i_number >= 0) {
        o_desc.o_data.i_unsigned = (i_number & cv_signed_long_max_);
        o_desc.o_data.b_negative = 0;
    } else {
        o_desc.o_data.i_unsigned = (-i_number & cv_signed_long_max_);
        o_desc.o_data.b_negative = 1;
    }
    o_desc.o_format = *(p_format);
    cv_file_print_number(p_file, &o_desc);
}

/*
 *
 */

void cv_file_print_unsigned( cv_file const * p_file,
    unsigned long i_number,
    cv_number_format const * p_format) {
    cv_number_desc o_desc = cv_number_desc_initializer_;
    o_desc.o_data.i_unsigned = i_number;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format = *(p_format);
    cv_file_print_number(p_file, &o_desc);
}

/*
 *
 */

void cv_file_print_nl( cv_file const * p_file) {
    cv_debug_assert_(p_file, cv_debug_code_null_ptr);
    cv_file_print_char(p_file, '\n');
}

/* end-of-file: cv_file_print.c */
