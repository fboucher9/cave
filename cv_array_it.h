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

cv_bool cv_array_it_read_char(
    cv_array_it * p_this,
    unsigned char * r_value);

cv_bool cv_array_it_read_ptr(
    cv_array_it * p_this,
    void const * * r_value);

cv_bool cv_array_it_read_array(
    cv_array_it * p_this,
    cv_array const * p_array);

cv_bool cv_array_it_write_char(
    cv_array_it * p_this,
    unsigned char c_data);

cv_bool cv_array_it_write_ptr(
    cv_array_it * p_this,
    void const * pc_void);

cv_bool cv_array_it_write_array(
    cv_array_it * p_this,
    cv_array const * p_array);

#endif /* #ifndef cv_array_it_h_ */

/* end-of-file: cv_array_it.h */
