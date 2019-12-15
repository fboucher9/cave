/* See LICENSE for license details */

#ifndef cv_file_print_h_
#define cv_file_print_h_

#include <cv_file/cv_file_pred.h>
#include <cv_algo/cv_array_pred.h>
#include <cv_number_pred.h>

void cv_file_print_char( cv_file const * p_file,
    unsigned char i_value);

void cv_file_print_array( cv_file const * p_file,
    cv_array const * p_array);

void cv_file_print_range( cv_file const * p_file,
    void const * p_range_min, void const * p_range_max);

void cv_file_print_vector( cv_file const * p_file,
    void const * p_buffer, long i_buffer_len);

void cv_file_print_0( cv_file const * p_file,
    char const * p_buffer, long i_max_len);

void cv_file_print_number( cv_file const * p_file,
    cv_number_desc const * p_desc);

void cv_file_print_signed( cv_file const * p_file,
    long i_number,
    cv_number_format const * p_format);

void cv_file_print_unsigned( cv_file const * p_file,
    unsigned long i_number,
    cv_number_format const * p_format);

void cv_file_print_nl( cv_file const * p_file);

#endif /* #ifndef cv_file_print_h_ */

/* end-of-file: cv_file_print.h */
