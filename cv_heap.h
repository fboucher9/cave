/* See LICENSE for license details */

#ifndef cv_heap_h_
#define cv_heap_h_

#include <cv_sizeof.h>

#include <cv_cast.h>

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

/*

Define a macros that help call of heap services.  The cv_new_ macro
automatically gets sizeof type and casts return to given type.  The
cv_delete_ macro casts object to void* for call to cv_heap_free.
Please note that there are no constructor or destructors called during these
new and delete macros.  Memory is zero initialized after alloc and cleanup
must be called before calling delete.

*/
#if ! defined cv_new_
#define cv_new_(type) \
    cv_cast_(type*, cv_heap_alloc(cv_sizeof_(type)))
#endif /* #if ! defined cv_heap_alloc */

#if ! defined cv_new_array_
#define cv_new_array_(type, count) \
    cv_cast_(type*, cv_heap_alloc(cv_cast_(long, cv_sizeof_(type) * (count))))
#endif

#if ! defined cv_delete_
#define cv_delete_(ptr) \
    (cv_heap_free(ptr))
#endif /* #if ! defined cv_delete_ */

#endif /* #ifndef cv_heap_h_ */
