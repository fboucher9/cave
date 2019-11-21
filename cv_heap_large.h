/* See LICENSE for license details */

#ifndef cv_heap_large_h_
#define cv_heap_large_h_

#include <cv_bool.h>

cv_bool cv_heap_large_load(void);

void cv_heap_large_unload(void);

void * cv_heap_large_alloc(
    long i_len);

void cv_heap_large_free(
    void * p_buf);

#endif /* #ifndef cv_heap_large_h_ */
