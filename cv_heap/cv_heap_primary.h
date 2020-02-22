/* See LICENSE for license details */

#ifndef cv_heap_primary_h_
#define cv_heap_primary_h_

/*

The cv_heap_primary module is a heap from which memory may be allocated but
never freed.  It may be used to allocate application context or allocate
memory from once callbacks.  It is used for small allocations maximum 1MB.

*/

#include <cv_heap/cv_heap_pred.h>
#include <cv_heap/cv_heap_section_lock.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

/*
 *
 */

struct cv_heap_primary {
    cv_heap_section_lock o_heap_section_lock;
};

cv_bool cv_heap_primary_init(cv_heap_primary * p_this);

void cv_heap_primary_cleanup(cv_heap_primary * p_this);

void * cv_heap_primary_alloc(cv_heap_primary * p_this, cv_uptr i_count);

#endif /* #ifndef cv_heap_primary_h_ */
