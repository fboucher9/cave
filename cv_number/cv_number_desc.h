/* See LICENSE for license details */

#ifndef cv_number_desc_h_
#define cv_number_desc_h_

/*
 *
 */

#include <cv_number/cv_number_pred.h>
#include <cv_number/cv_number_format.h>

/*
 *
 */

struct cv_number_data {
    unsigned long i_unsigned;
    unsigned long b_negative;
};

#define cv_number_data_initializer_ { 0, 0 }

/* Verify sizeof data members */
typedef char cv_verify_sizeof_number_data [
    (sizeof(signed long) == sizeof(unsigned long))
    ? 1 : -1 ];

/*
 *
 */

struct cv_number_desc {
    cv_number_data o_data;
    /* -- */
    cv_number_format o_format;
};

#define cv_number_desc_initializer_ \
{ /* .o_data */ cv_number_data_initializer_, \
  /* .o_format */ cv_number_format_initializer_ }

void cv_number_desc_init( cv_number_desc * p_this);

void cv_number_desc_cleanup( cv_number_desc * p_this);

#endif /* #ifndef cv_number_desc_h_ */

/* end-of-file: cv_number_desc.h */
