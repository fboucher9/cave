/* See LICENSE for license details */

#ifndef cv_array_0_h_
#define cv_array_0_h_

#include <cv_algo/cv_array_pred.h>
#include <cv_algo/cv_buffer.h>
#include <cv_misc/cv_bool.h>

struct cv_array_0 {
    cv_buffer o_buffer;
};

cv_bool cv_array_0_init( cv_array_0 * p_this, cv_array const * p_string);
void cv_array_0_cleanup( cv_array_0 * p_this);
char const * cv_array_0_get( cv_array_0 const * p_this);
cv_uptr cv_array_0_len( cv_array_0 const * p_this);

#endif /* #ifndef cv_array_0_h_ */
