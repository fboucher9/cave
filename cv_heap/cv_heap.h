/* See LICENSE for license details */

#ifndef cv_heap_h_
#define cv_heap_h_

/*

Memory management services.  Allocate memory from heap or free memory back
to heap.  These function offer features such as leak detection, boundary
checks and statistics.  The heap is designed to avoid fragmentation issues.
Performance is not optimal so it is suggested to allocate memory during
initialization phase of application.

*/

void * cv_heap_alloc(
    long i_buffer_length);

void cv_heap_free(
    void * p_buffer);

#endif /* #ifndef cv_heap_h_ */

/* end-of-file: cv_heap.h */
