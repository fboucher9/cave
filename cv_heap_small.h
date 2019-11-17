/* See LICENSE for license details */

#ifndef cv_heap_small_h_
#define cv_heap_small_h_

/*

Heap for allocations with small length, less than 4KB.

*/

void * cv_heap_small_alloc(
    long i_len);

void cv_heap_small_free(
    void * p_buf);

#endif /* #ifndef cv_heap_small_h_ */
