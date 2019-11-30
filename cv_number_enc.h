/* See LICENSE for license details */

#ifndef cv_number_enc_h_
#define cv_number_enc_h_

/*

Module: cv_number_enc.h

Description: Encode of numbers to a text representation.  This is designed to
replace functionality of printf.  Options are provided with a descriptor
structure instead of a format string.

*/

#include <cv_types.h>

#include <cv_bool.h>

#include <cv_string_pred.h>

#include <cv_number_pred.h>

#include <cv_number_desc.h>

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

typedef enum cv_number_status {
    cv_number_status_continue = 0,
    cv_number_status_done = 1,
    cv_number_status_full = 2,
    cv_number_status_fail = 3
} cv_number_status;

/* state-machine services */
cv_bool cv_number_enc_init(
    cv_number_enc * p_this,
    cv_number_desc const * p_desc);

void cv_number_enc_cleanup(
    cv_number_enc * p_this);

cv_number_status cv_number_enc_read(
    cv_number_enc * p_this,
    cv_string_it * p_string_it);

/* all-in-one service */
cv_number_status cv_number_enc_convert(
    cv_number_desc const * p_desc,
    cv_string_it * p_string_it);

#endif /* #ifndef cv_number_enc_h_ */

/* end-of-file: cv_number_enc.h */
