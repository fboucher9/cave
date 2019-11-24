/* See LICENSE for license details */

#ifndef cv_buffer_h_
#define cv_buffer_h_

#include <cv_buffer_pred.h>

#include <cv_array.h>

#include <cv_bool.h>

struct cv_buffer
{
    cv_array o_array;
};

#define cv_buffer_initializer_ { cv_array_initializer_ }

cv_bool cv_buffer_init(
    cv_buffer * p_this);

void cv_buffer_cleanup(
    cv_buffer * p_this);

cv_bool cv_buffer_realloc(
    cv_buffer * p_this,
    long i_length);

long cv_buffer_char_count(
    cv_buffer const * p_this);

#endif /* #ifndef cv_buffer_h_ */
