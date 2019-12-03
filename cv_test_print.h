/* See LICENSE for license details */

#ifndef cv_test_print_h_
#define cv_test_print_h_

#include <cv_array_pred.h>
#include <cv_number_pred.h>

void cv_print_array( cv_array const * p_array);

void cv_print_0( char const * p_array0, long i_array0_max_len);

void cv_print_number( cv_number_desc const * p_desc);

void cv_print_signed( long i_number, cv_number_format const * p_format);

void cv_print_unsigned( unsigned long i_number,
    cv_number_format const * p_format);

void cv_print_dec( long i_number);

void cv_print_hex( unsigned long i_number);

void cv_print_nl(void);

#endif /* #ifndef cv_test_print_h_ */

/* end-of-file: cv_test_print.h */
