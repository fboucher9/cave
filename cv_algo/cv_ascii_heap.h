/* See LICENSE for license details */

#ifndef cv_ascii_heap_h_
#define cv_ascii_heap_h_

#include <cv_algo/cv_ascii_data.h>

struct cv_ascii_heap {
    cv_ascii_data o_base;
};

void cv_ascii_heap_init(cv_ascii_heap * p_this);
void cv_ascii_heap_cleanup(cv_ascii_heap * p_this);
cv_bool cv_ascii_heap_resize(cv_ascii_heap * p_this,
    cv_uptr i_len);
cv_bool cv_ascii_heap_dup(cv_ascii_heap * p_this,
    cv_ascii_code const * p_ref);
cv_uptr cv_ascii_heap_len(cv_ascii_heap const * p_this);

#endif /* #ifndef cv_ascii_heap_h_ */

/* end-of-file: cv_ascii_heap.h */
