/* See LICENSE for license details */

#ifndef cv_array_it_h_
#define cv_array_it_h_

#include <cv_algo/cv_array_pred.h>

#include <cv_algo/cv_array.h>

#include <cv_misc/cv_bool.h>

struct cv_array_it
{
    cv_array o_array;
};

#define cv_array_it_initializer_ { cv_array_null_ }

void cv_array_it_init(
    cv_array_it * p_this,
    cv_array const * p_array);

void cv_array_it_init_vector(
    cv_array_it * p_this,
    void const * p_buf,
    long i_len);

void cv_array_it_init_range(
    cv_array_it * p_this,
    void const * p_range_min,
    void const * p_range_max);

void cv_array_it_cleanup(
    cv_array_it * p_this);

cv_bool cv_array_it_get_next_char(
    cv_array_it * p_this,
    cv_array_ptr * r_value);

cv_bool cv_array_it_get_next_ptr(
    cv_array_it * p_this,
    cv_array_ptr * r_value);

cv_bool cv_array_it_get_next_array(
    cv_array_it * p_this,
    long i_array_len,
    cv_array_ptr * r_value);

cv_bool cv_array_it_read_next_char(
    cv_array_it * p_this,
    unsigned char * r_value);

cv_bool cv_array_it_read_next_ptr(
    cv_array_it * p_this,
    void const * * r_value);

cv_bool cv_array_it_read_next_array(
    cv_array_it * p_this,
    cv_array const * p_array);

cv_bool cv_array_it_write_next_char(
    cv_array_it * p_this,
    unsigned char c_data);

cv_bool cv_array_it_write_next_ptr(
    cv_array_it * p_this,
    void const * pc_void);

cv_bool cv_array_it_write_next_array(
    cv_array_it * p_this,
    cv_array const * p_array);

#endif /* #ifndef cv_array_it_h_ */

/* end-of-file: cv_array_it.h */
