/* See LICENSE for license details */

#ifndef cv_file_print_h_
#define cv_file_print_h_

#include <cv_file_pred.h>
#include <cv_array_pred.h>
#include <cv_number_pred.h>

void cv_file_print_array( cv_file const * p_file,
    cv_array const * p_array);

void cv_file_print_number( cv_file const * p_file,
    cv_number_desc const * p_desc);

void cv_file_print_nl( cv_file const * p_file);

#endif /* #ifndef cv_file_print_h_ */

/* end-of-file: cv_file_print.h */