/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_array_print.h>
#include <cv_algo/cv_array_it.h>
#include <cv_algo/cv_array.h>
#include <cv_number/cv_number_enc.h>
#include <cv_misc/cv_limits.h>

/*
 *
 */

cv_bool cv_array_print( cv_array_it * p_array_it,
    cv_array const * p_array) {
    return cv_array_it_write_next_array( p_array_it, p_array);
}

/*
 *
 */

cv_bool cv_array_print_0( cv_array_it * p_array_it,
    char const * p_buf_0, cv_uptr i_max_len) {
    cv_bool b_result = cv_false;
    cv_array o_array = cv_array_null_;
    cv_array_init_0(&o_array, p_buf_0, i_max_len);
    b_result = cv_array_print(p_array_it, &o_array);
    cv_array_cleanup(&o_array);
    return b_result;
}

/*
 *
 */

cv_bool cv_array_print_vector( cv_array_it * p_array_it,
    void const * p_buf, cv_uptr i_buf_len) {
    cv_bool b_result = cv_false;
    cv_array o_array = cv_array_null_;
    cv_array_init_vector(&o_array, p_buf, i_buf_len);
    b_result = cv_array_print(p_array_it, &o_array);
    cv_array_cleanup(&o_array);
    return b_result;
}

/*
 *
 */

cv_bool cv_array_print_range(
    cv_array_it * p_array_it,
    void const * p_range_min,
    void const * p_range_max) {
    cv_bool b_result = cv_false;
    cv_array o_array = cv_array_null_;
    cv_array_init_range(&o_array, p_range_min, p_range_max);
    b_result = cv_array_print(p_array_it, &o_array);
    cv_array_cleanup(&o_array);
    return b_result;
}

/*
 *
 */

cv_bool cv_array_print_char(
    cv_array_it * p_array_it,
    unsigned char const i_value) {
    return cv_array_it_write_next_char(p_array_it, i_value);
}

/*
 *
 */

cv_bool cv_array_print_nl(
    cv_array_it * p_array_it) {
    return cv_array_it_write_next_char(p_array_it, '\n');
}

/*
 *
 */

cv_bool cv_array_print_number(
    cv_array_it * p_array_it,
    cv_number_desc const * p_number_desc) {
    cv_bool b_result = cv_false;
    cv_number_enc o_number_enc = cv_number_enc_initializer_;
    if (cv_number_enc_init(&o_number_enc, p_number_desc)) {
        cv_number_status const e_number_status = cv_number_enc_read(
            &o_number_enc, p_array_it);
        if (cv_number_status_done == e_number_status) {
            b_result = cv_true;
        }
        cv_number_enc_cleanup(&o_number_enc);
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_array_print_signed(
    cv_array_it * p_array_it,
    long i_number,
    cv_number_format const * p_format) {
    cv_number_desc o_number_desc = cv_number_desc_initializer_;
    if (i_number >= 0) {
        o_number_desc.o_data.i_unsigned = (i_number & cv_signed_long_max_);
        o_number_desc.o_data.b_negative = 0;
    } else {
        o_number_desc.o_data.i_unsigned = (-i_number & cv_signed_long_max_);
        o_number_desc.o_data.b_negative = 1;
    }
    o_number_desc.o_format = *p_format;
    return cv_array_print_number(p_array_it, &o_number_desc);
}

/*
 *
 */

cv_bool cv_array_print_unsigned(
    cv_array_it * p_array_it,
    unsigned long i_number,
    cv_number_format const * p_format) {
    cv_number_desc o_number_desc = cv_number_desc_initializer_;
    o_number_desc.o_data.i_unsigned = i_number;
    o_number_desc.o_data.b_negative = 0;
    o_number_desc.o_format = *p_format;
    return cv_array_print_number(p_array_it, &o_number_desc);
}

/* end-of-file: cv_array_print.c */
