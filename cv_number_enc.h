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

enum cv_number_flag
{
    cv_number_flag_unsigned = 1,

    cv_number_flag_hexadecimal = 2,

    cv_number_flag_upper = 4

};

struct cv_number_enc
{
    cv_number_desc o_desc;
    /* -- */
    long i_state;
    long i_state_count;
    /* -- */
    unsigned char a_digit[30u];
    unsigned char i_digit_count;
    char b_negative;
};

#define cv_number_enc_initializer_ \
{ cv_number_desc_initializer_, 0, 0, {0}, 0, 0 }

typedef enum cv_number_status
{
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
