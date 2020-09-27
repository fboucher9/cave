/* See LICENSE for license details */

#ifndef cv_array_heap_h_
#define cv_array_heap_h_

#include <cv_algo/cv_array_pred.h>
#include <cv_algo/cv_array.h>
#include <cv_misc/cv_bool.h>

struct cv_array_heap {
    cv_array o_array;
};

cv_bool cv_array_heap_init( cv_array_heap * p_this, cv_uptr i_length,
    char const * p_class, cv_uptr i_instance);
void cv_array_heap_cleanup( cv_array_heap * p_this);
cv_uptr cv_array_heap_len( cv_array_heap const * p_this);

#endif /* #ifndef cv_array_heap_h_ */
