/* See LICENSE for license details */

#ifndef cv_number_print_h_
#define cv_number_print_h_

/*
 *
 */

#include <cv_number/cv_number_pred.h>
#include <cv_algo/cv_array_pred.h>

long cv_number_print( cv_number_desc const * p_desc,
    cv_array const * p_array);

long cv_number_print_signed( long i_number,
    cv_number_format const * p_format,
    cv_array const * p_array);

long cv_number_print_unsigned( unsigned long i_number,
    cv_number_format const * p_format,
    cv_array const * p_array);

#endif /* #ifndef cv_number_print_h_ */

/* end-of-file: cv_number_print.h */
