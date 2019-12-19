/* See LICENSE for license details */

#ifndef cv_number_enc_h_
#define cv_number_enc_h_

/*

Module: cv_number_enc.h

Description: Encode of numbers to a text representation.  This is designed to
replace functionality of printf.  Options are provided with a descriptor
structure instead of a format string.

*/

#include <cv_misc/cv_types.h>

#include <cv_misc/cv_bool.h>

#include <cv_algo/cv_array_pred.h>

#include <cv_number/cv_number_pred.h>

#include <cv_number/cv_number_desc.h>

#include <cv_number/cv_number_status.h>

struct cv_number_enc {
    cv_number_desc o_desc;
    /* -- */
    short i_state;
    short i_before_space;
    short i_after_space;
    short i_before_zero;
    /* -- */
    short i_digit_count;
    short i_after_zero;
    short s_padding[2u];
    /* -- */
    char b_sign;
    char b_dot;
    unsigned char a_sign[1u];
    unsigned char a_digit[29u];
};

#define cv_number_enc_initializer_ \
{ cv_number_desc_initializer_, 0, 0, 0, 0, 0, 0, {0}, 0, 0, {0}, {0} }

/* state-machine services */
cv_bool cv_number_enc_init(
    cv_number_enc * p_this,
    cv_number_desc const * p_desc);

void cv_number_enc_cleanup(
    cv_number_enc * p_this);

cv_number_status cv_number_enc_read(
    cv_number_enc * p_this,
    cv_array_it * p_array_it);

/* all-in-one service */
cv_number_status cv_number_enc_convert(
    cv_number_desc const * p_desc,
    cv_array const * p_input_array,
    cv_array * p_output_array);

#endif /* #ifndef cv_number_enc_h_ */

/* end-of-file: cv_number_enc.h */
