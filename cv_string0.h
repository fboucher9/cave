/* See LICENSE for license details */

#ifndef cv_string0_h_
#define cv_string0_h_

#include <cv_string_pred.h>

#include <cv_string1.h>

#include <cv_bool.h>

struct cv_string0
{
    cv_string1 o_buf1;
};

#define cv_string0_initializer_ { cv_string1_initializer_ }

cv_bool cv_string0_init(
    cv_string0 * p_this,
    cv_string const * p_string);

void cv_string0_cleanup(
    cv_string0 * p_this);

char const * cv_string0_get(
    cv_string0 const * p_this);

long cv_string0_len(
    cv_string0 const * p_this);

#endif /* #ifndef cv_string0_h_ */
