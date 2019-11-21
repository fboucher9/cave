/* See LICENSE for license details */

#ifndef cv_heap_small_h_
#define cv_heap_small_h_

/*

Heap for allocations with small length, less than 4KB.

*/

#include <cv_bool.h>

#define cv_heap_small_max_len_ (4096)

cv_bool cv_heap_small_load(void);

void cv_heap_small_unload(void);

void * cv_heap_small_alloc(
    long i_len);

void cv_heap_small_free(
    void * p_buf);

#endif /* #ifndef cv_heap_small_h_ */
