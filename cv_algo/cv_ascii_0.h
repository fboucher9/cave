/* See LICENSE for license details */

#ifndef cv_ascii_0_h_
#define cv_ascii_0_h_

#include <cv_algo/cv_ascii_heap.h>

struct cv_ascii_0 {
    cv_ascii_heap o_heap;
};

void cv_ascii_0_init(cv_ascii_0 * p_this);
void cv_ascii_0_cleanup(cv_ascii_0 * p_this);
cv_bool cv_ascii_0_dup(cv_ascii_0 * p_this,
    cv_ascii_code const * p_ref);

#endif /* #ifndef cv_ascii_0_h_ */

/* end-of-file: cv_ascii_0.h */
