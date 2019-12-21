/* See LICENSE for license details */

#ifndef cv_buffer_h_
#define cv_buffer_h_

#include <cv_algo/cv_buffer_pred.h>

#include <cv_algo/cv_array.h>

#include <cv_misc/cv_bool.h>

struct cv_buffer
{
    cv_array o_array;
};

#define cv_buffer_initializer_ { cv_array_null_ }

cv_bool cv_buffer_init(
    cv_buffer * p_this,
    cv_uptr i_length);

void cv_buffer_cleanup(
    cv_buffer * p_this);

cv_uptr cv_buffer_len(
    cv_buffer const * p_this);

#endif /* #ifndef cv_buffer_h_ */
