/* See LICENSE for license details */

#ifndef cv_string_it_h_
#define cv_string_it_h_

#include <cv_string_pred.h>

#include <cv_string.h>

#include <cv_bool.h>

struct cv_string_it
{
    cv_string o_string;
};

cv_bool cv_string_it_init(
    cv_string_it * p_string_it,
    cv_string const * p_string);

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
    cv_string const * p_string);

cv_bool cv_string_it_read_array(
    cv_string_it * p_string_it,
    cv_string const * p_string);

#endif /* #ifndef cv_string_it_h_ */

/* end-of-file: cv_string_it.h */
