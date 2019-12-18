/* See LICENSE for license details */

#ifndef cv_number_dec_h_
#define cv_number_dec_h_

/*
 *  Module: cv_number_dec.h
 *
 *  Description: Decode text buffer and output a number.
 */

#include <cv_number_pred.h>
#include <cv_algo/cv_array_pred.h>
#include <cv_number_desc.h>
#include <cv_number_status.h>

/*
 *
 */

struct cv_number_dec {
    cv_number_desc o_desc;
    /* -- */
    int i_state;
    unsigned int i_base;
};

#define cv_number_dec_initializer_ \
{ cv_number_desc_initializer_, 0, 0 }

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

int cv_number_dec_step(
    cv_number_dec * p_this,
    cv_array_it * p_array_it);

#endif /* #ifndef cv_number_dec_h_ */

/* end-of-file: cv_number_dec.h */
