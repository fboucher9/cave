/* See LICENSE for license details */

#ifndef cv_heap_secondary_h_
#define cv_heap_secondary_h_

/*
 *
 */

#include <cv_heap/cv_heap_pred.h>
#include <cv_heap/cv_heap_section_lock.h>

/*
 *
 */

struct cv_heap_secondary {
    cv_heap_section_lock o_heap_section_lock;
};

#define cv_heap_secondary_initializer_ \
{ cv_heap_section_lock_initializer_ }

cv_bool cv_heap_secondary_init( cv_heap_secondary * p_this);

void cv_heap_secondary_cleanup( cv_heap_secondary * p_this);

void * cv_heap_secondary_alloc( cv_heap_secondary * p_this, long i_len);

#endif /* #ifndef cv_heap_secondary_h_ */

/* end-of-file: cv_heap_secondary.h */
