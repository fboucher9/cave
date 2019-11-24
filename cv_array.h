/* See LICENSE for license details */

#ifndef cv_array_h_
#define cv_array_h_

/*

Utilities for arrays.

*/

#include <cv_array_pred.h>

#include <cv_array_ptr.h>

#include <cv_bool.h>

struct cv_array
{
    cv_array_ptr o_min;
    cv_array_ptr o_max;
};

#define cv_array_initializer_ { cv_array_ptr_null_, cv_array_ptr_null_ }

cv_bool cv_array_init(
    cv_array * p_array,
    void const * p_ref_min,
    void const * p_ref_max);

void cv_array_cleanup(
    cv_array * p_array);

#endif /* #ifndef cv_array_h_ */
