/* See LICENSE for license details */

#ifndef cv_heap_primary_h_
#define cv_heap_primary_h_

/*

The cv_heap_primary module is a heap from which memory may be allocated but
never freed.  It may be used to allocate application context or allocate
memory from once callbacks.  It is used for small allocations maximum 1MB.

*/

void * cv_heap_primary_alloc(
    long i_count);

#endif /* #ifndef cv_heap_primary_h_ */
