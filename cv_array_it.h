/* See LICENSE for license details */

#ifndef cv_array_it_h_
#define cv_array_it_h_

#include <cv_array_pred.h>

#include <cv_array.h>

#include <cv_bool.h>

struct cv_array_it
{
    cv_array o_array;
};

#define cv_array_it_initializer_ { cv_array_initializer_ }

cv_bool cv_array_it_init(
    cv_array_it * p_this,
    cv_array const * p_array);

void cv_array_it_cleanup(
    cv_array_it * p_this);

cv_bool cv_array_it_next(
    cv_array_it * p_this,
    long i_sizeof_object,
    cv_array_ptr * r_cur);

#endif /* #ifndef cv_array_it_h_ */

/* end-of-file: cv_array_it.h */
