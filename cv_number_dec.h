/* See LICENSE for license details */

#ifndef cv_number_dec_h_
#define cv_number_dec_h_

/*
 *  Module: cv_number_dec.h
 *
 *  Description: Decode text buffer and output a number.
 */

struct cv_number_dec {
    cv_number_desc o_desc;
    /* -- */
};

void cv_number_dec_init(
    cv_number_dec * p_this);

void cv_number_dec_cleanup(
    cv_number_dec * p_this);

/*  States:
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
