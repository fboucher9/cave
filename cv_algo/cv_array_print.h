/* See LICENSE for license details */

#ifndef cv_array_print_h_
#define cv_array_print_h_

/*
 *
 */

#include <cv_algo/cv_array_pred.h>
#include <cv_number/cv_number_pred.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

cv_bool cv_array_print( cv_array_it * p_array_it,
    cv_array const * p_array);

cv_bool cv_array_print_0( cv_array_it * p_array_it,
    char const * p_buf_0, cv_uptr i_max_len);

cv_bool cv_array_print_vector( cv_array_it * p_array_it,
    void const * p_buf, cv_uptr i_buf_len);

cv_bool cv_array_print_range( cv_array_it * p_array_it,
    void const * p_range_min, void const * p_range_max);

cv_bool cv_array_print_char( cv_array_it * p_array_it,
    unsigned char const i_value);

cv_bool cv_array_print_nl( cv_array_it * p_array_it);

cv_bool cv_array_print_number( cv_array_it * p_array_it,
    cv_number_desc const * p_number_desc);

cv_bool cv_array_print_signed( cv_array_it * p_array_it,
    long i_number, cv_number_format const * p_format);

cv_bool cv_array_print_unsigned( cv_array_it * p_array_it,
    unsigned long i_number, cv_number_format const * p_format);

#endif /* #ifndef cv_array_print_h_ */

/* end-of-file: cv_array_print.h */
