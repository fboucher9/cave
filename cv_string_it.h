/* See LICENSE for license details */

#ifndef cv_string_it_h_
#define cv_string_it_h_

#include <cv_string_pred.h>

#include <cv_array.h>

#include <cv_bool.h>

struct cv_string_it
{
    cv_array o_array;
};

#define cv_string_it_initializer_ { cv_array_initializer_ }

cv_bool cv_string_it_init(
    cv_string_it * p_string_it,
    cv_array const * p_array);

void cv_string_it_cleanup(
    cv_string_it * p_string_it);

cv_bool cv_string_it_write_char(
    cv_string_it * p_string_it,
    unsigned char c_data);

cv_bool cv_string_it_read_char(
    cv_string_it * p_string_it,
    unsigned char * r_data);

cv_bool cv_string_it_write_array(
    cv_string_it * p_string_it,
    cv_array const * p_array);

cv_bool cv_string_it_read_array(
    cv_string_it * p_string_it,
    cv_array const * p_array);

#endif /* #ifndef cv_string_it_h_ */

/* end-of-file: cv_string_it.h */
