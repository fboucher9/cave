/* See LICENSE for license details */

#ifndef cv_string1_h_
#define cv_string1_h_

#include <cv_string_pred.h>

#include <cv_string.h>

#include <cv_bool.h>

struct cv_string1
{
    cv_string o_buf;
};

#define cv_string1_initializer_ { cv_string_initializer_ }

cv_bool cv_string1_init(
    cv_string1 * p_this,
    long i_length);

void cv_string1_cleanup(
    cv_string1 * p_this);

long cv_string1_len(
    cv_string1 const * p_this);

#endif /* #ifndef cv_string1_h_ */
