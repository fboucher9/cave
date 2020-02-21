/* See LICENSE for license details */

#ifndef cv_array_h_
#define cv_array_h_

/*

Utilities for arrays.

*/

#include <cv_algo/cv_array_pred.h>
#include <cv_algo/cv_array_ptr.h>
#include <cv_misc/cv_types.h>

struct cv_array {
    cv_array_ptr o_min;
    cv_array_ptr o_max;
};

#define cv_array_initializer_(pc_min, pc_max) { \
    cv_ptr_initializer_(pc_min), \
    cv_ptr_initializer_(pc_max) \
}

void cv_array_init( cv_array * p_array);
void cv_array_init_ref( cv_array * p_array, cv_array const * p_ref);
void cv_array_init_range( cv_array * p_array,
    void const * p_ref_min, void const * p_ref_max);
void cv_array_init_0( cv_array * p_array,
    char const * p_ref0, cv_uptr i_ref0_max_len);
void cv_array_init_vector( cv_array * p_array,
    void const * p_buf, cv_uptr i_buf_len);
void cv_array_cleanup( cv_array * p_array);
cv_uptr cv_array_len( cv_array const * p_array);

#endif /* #ifndef cv_array_h_ */
