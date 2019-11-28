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

#define cv_array_null_ { cv_ptr_null_, cv_ptr_null_ }

#define cv_array_initializer_(pc_min, pc_max) \
{ \
    cv_ptr_initializer_(pc_min), \
    cv_ptr_initializer_(pc_max) \
}

cv_bool cv_array_init(
    cv_array * p_array);

cv_bool cv_array_init_ref(
    cv_array * p_array,
    cv_array const * p_ref);

cv_bool cv_array_init_range(
    cv_array * p_array,
    void const * p_ref_min,
    void const * p_ref_max);

cv_bool cv_array_init_0(
    cv_array * p_array,
    char const * p_ref0,
    long i_ref0_max_len);

void cv_array_cleanup(
    cv_array * p_array);

long cv_array_len(
    cv_array const * p_array);

long cv_array_short_count(
    cv_array const * p_array);

long cv_array_int_count(
    cv_array const * p_array);

long cv_array_long_count(
    cv_array const * p_array);

long cv_array_ll_count(
    cv_array const * p_array);

long cv_array_ptr_count(
    cv_array const * p_array);

#endif /* #ifndef cv_array_h_ */
