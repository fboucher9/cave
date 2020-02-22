/* See LICENSE for license details */

#ifndef cv_heap_section_lock_h_
#define cv_heap_section_lock_h_

/*
 *  Module: cv_heap_section_lock.h
 *
 *  Description: Thread-safe version of cv_heap_section object.
 */

#include <cv_heap/cv_heap_pred.h>
#include <cv_thread/cv_mutex.h>
#include <cv_heap/cv_heap_section.h>
#include <cv_misc/cv_types.h>

struct cv_heap_section_lock {
    cv_mutex o_mutex;
    cv_heap_section o_heap_section;
};

cv_bool cv_heap_section_lock_init(
    cv_heap_section_lock * p_this,
    cv_heap_section_desc const * p_desc);

void cv_heap_section_lock_cleanup(
    cv_heap_section_lock * p_this);

void * cv_heap_section_lock_alloc(
    cv_heap_section_lock * p_this,
    cv_uptr i_len);

#endif /* #ifndef cv_heap_section_lock_h_ */

/* end-of-file: cv_heap_section_lock.h */
