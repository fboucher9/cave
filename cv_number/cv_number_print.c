/* See LICENSE for license details */

/*
 *
 */

#include <cv_number/cv_number_print.h>
#include <cv_number/cv_number_enc.h>
#include <cv_algo/cv_array_it.h>
#include <cv_misc/cv_limits.h>

/*
 *
 */

cv_uptr cv_number_print( cv_number_desc const * p_desc,
    cv_array const * p_array) {
    cv_uptr i_result = 0;
    cv_array o_array_out = {0};
    cv_array_init(&o_array_out);
    if (cv_number_status_done == cv_number_enc_convert(
            p_desc, p_array, &o_array_out)) {
        i_result = cv_array_len(&o_array_out);
    }
    cv_array_cleanup(&o_array_out);
    return i_result;
}

/*
 *
 */

cv_uptr cv_number_print_signed( long i_number,
    cv_number_format const * p_format,
    cv_array const * p_array) {
    cv_uptr i_result = 0;
    cv_number_desc o_desc = {0};
    cv_number_desc_init(&o_desc);
    if (i_number < 0) {
        o_desc.o_data.i_unsigned = (-i_number) & cv_signed_long_max_;
        o_desc.o_data.b_negative = 1;
    } else {
        o_desc.o_data.i_unsigned = i_number & cv_signed_long_max_;
        o_desc.o_data.b_negative = 0;
    }
    o_desc.o_format = *p_format;
    i_result = cv_number_print( &o_desc, p_array);
    cv_number_desc_cleanup(&o_desc);
    return i_result;
}

/*
 *
 */

cv_uptr cv_number_print_unsigned( unsigned long i_number,
    cv_number_format const * p_format,
    cv_array const * p_array) {
    cv_uptr i_result = 0;
    cv_number_desc o_desc = {0};
    cv_number_desc_init(&o_desc);
    o_desc.o_data.i_unsigned = i_number;
    o_desc.o_data.b_negative = 0;
    o_desc.o_format = *p_format;
    i_result = cv_number_print( &o_desc, p_array);
    cv_number_desc_cleanup(&o_desc);
    return i_result;
}

/* end-of-file: cv_number_print.c */
