/* See LICENSE for license details */

#ifndef cv_number_dec_h_
#define cv_number_dec_h_

/*
 *  Module: cv_number_dec.h
 *
 *  Description: Decode text buffer and output a number.
 */

#include <cv_number/cv_number_pred.h>
#include <cv_algo/cv_array_pred.h>
#include <cv_number/cv_number_desc.h>
#include <cv_number/cv_number_status.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_number_dec {
    cv_number_desc x_desc;
    /* -- */
    int i_state;
    int i_padding[1u];
};

/*
 *
 */

void cv_number_dec_init(
    cv_number_dec * p_this,
    unsigned int i_base);

void cv_number_dec_cleanup(
    cv_number_dec * p_this);

/*  Returns:
 *      -   continue
 *      -   more data
 *      -   done
 *      -   error
 *
 *  Comments:
 *      -   number must be terminated by a space or an invalid character
 *          at the end of the string.
 */

int cv_number_dec_write( cv_number_dec * p_this, cv_array_it * p_array_it);

cv_bool cv_number_dec_read( cv_number_dec * p_this, cv_number_desc * r_value);

#endif /* #ifndef cv_number_dec_h_ */

/* end-of-file: cv_number_dec.h */
