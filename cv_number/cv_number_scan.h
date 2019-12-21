/* See LICENSE for license details */

#ifndef cv_number_scan_h_
#define cv_number_scan_h_

/*
 *
 */

#include <cv_algo/cv_array_pred.h>
#include <cv_misc/cv_types.h>

long cv_number_scan_array( cv_array const * p_array, unsigned int i_base);

long cv_number_scan_range( void const * p_range_min,
    void const * p_range_max, unsigned int i_base);

long cv_number_scan_vector( void const * p_buffer, cv_uptr i_buffer_len,
    unsigned int i_base);

long cv_number_scan_0( char const * p_text, cv_uptr i_max_len,
    unsigned int i_base);

#endif /* #ifndef cv_number_scan_h_ */

/* end-of-file: cv_number_scan.h */
