/* See LICENSE for license details */

/*
 *
 */

#include <cv_number_scan.h>
#include <cv_number_dec.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_it.h>
#include <cv_misc/cv_limits.h>

/*
 *
 */

long cv_number_scan_array( cv_array const * p_array, unsigned int i_base) {
    long i_result = 0;
    cv_array_it o_array_it = cv_array_it_initializer_;
    cv_number_dec o_number_dec = cv_number_dec_initializer_;
    cv_array_it_init(&o_array_it, p_array);
    cv_number_dec_init(&o_number_dec, i_base);
    while (cv_number_status_continue == cv_number_dec_step(&o_number_dec,
            &o_array_it)) {
    }
    i_result = (o_number_dec.o_desc.o_data.i_unsigned
        & cv_signed_long_max_);
    if (o_number_dec.o_desc.o_data.b_negative) {
        i_result = -i_result;
    }
    cv_number_dec_cleanup(&o_number_dec);
    cv_array_it_cleanup(&o_array_it);
    return i_result;
}

/*
 *
 */

long cv_number_scan_range( void const * p_range_min,
    void const * p_range_max, unsigned int i_base) {
    long i_result = 0;
    cv_array o_array = cv_array_null_;
    cv_array_init_range(&o_array, p_range_min, p_range_max);
    i_result = cv_number_scan_array(&o_array, i_base);
    cv_array_cleanup(&o_array);
    return i_result;
}

/*
 *
 */

long cv_number_scan_vector( void const * p_buffer, long i_buffer_len,
    unsigned int i_base) {
    long i_result = 0;
    cv_array o_array = cv_array_null_;
    cv_array_init_vector(&o_array, p_buffer, i_buffer_len);
    i_result = cv_number_scan_array(&o_array, i_base);
    cv_array_cleanup(&o_array);
    return i_result;
}

/*
 *
 */

long cv_number_scan_0( char const * p_text, long i_max_len,
    unsigned int i_base) {
    long i_result = 0;
    cv_array o_array = cv_array_null_;
    cv_array_init_0(&o_array, p_text, i_max_len);
    i_result = cv_number_scan_array(&o_array, i_base);
    cv_array_cleanup(&o_array);
    return i_result;
}

/* end-of-file: cv_number_scan.c */
