/* See LICENSE for license details */

/*
 *
 */

#include <cv_file/cv_file_print.h>
#include <cv_file/cv_file.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_debug.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_number_enc.h>
#include <cv_misc/cv_convert.h>

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
        long const i_write_result = cv_file_write(
            p_file,
            & o_array_it);
        if (i_write_result > 0) {
            o_array_it.o_min.pc_char += i_write_result;
        } else {
            b_result = cv_false;
        }
    }
    cv_array_cleanup(&o_array_it);
}

/*
 *
 */

void cv_file_print_number( cv_file const * p_file,
    cv_number_desc const * p_desc) {
    char c_buffer[64u];
    cv_array o_buffer = cv_array_null_;
    cv_debug_assert_(p_file && p_desc, cv_debug_code_null_ptr);
    cv_array_init_vector(&o_buffer, c_buffer, cv_sizeof_(c_buffer));
    {
        cv_array o_result = cv_array_null_;
        cv_array_init(&o_result);
        if (cv_number_status_done ==
            cv_number_enc_convert(p_desc, &o_buffer, &o_result)) {
            cv_file_print_array(p_file, &o_result);
        }
        cv_array_cleanup(&o_result);
    }
    cv_array_cleanup(&o_buffer);
}

/*
 *
 */

void cv_file_print_signed( cv_file const * p_file,
    long i_number,
    cv_number_format const * p_format) {
    cv_number_desc o_desc = cv_number_desc_initializer_;
    if (i_number >= 0) {
        o_desc.o_data.i_unsigned = cv_convert_l2u_(i_number);
        o_desc.o_data.b_negative = 0;
    } else {
        o_desc.o_data.i_unsigned = cv_convert_l2u_(-i_number);
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

static cv_array const * get_nl_array(void) {
    static unsigned char a_text[] = { '\n' };
    static cv_array const g_text = cv_array_text_initializer_(a_text);
    return &g_text;
}

/*
 *
 */

void cv_file_print_nl( cv_file const * p_file) {
    cv_debug_assert_(!!p_file, cv_debug_code_null_ptr);
    cv_file_print_array(p_file, get_nl_array());
}

/* end-of-file: cv_file_print.c */
