/* See LICENSE for license details */

#ifndef cv_object_h_
#define cv_object_h_

/*
 *  Module: cv_object.h
 *
 *  Description:
 *
 *      Helper functions to construction and destruction of objects.  Memory
 *      for objects may be allocated on heap or allocated by caller.
 */

#include <cv_algo/cv_unique.h>
#include <cv_misc/cv_types.h>
#include <cv_thread/cv_mutex_impl.h>

typedef struct cv_object cv_object;

struct cv_object {
    cv_uptr i_placement_len;
    cv_sptr i_leak_count;
    /* -- */
    cv_unique o_unique;
    /* -- */
    cv_mutex o_mutex;
    /* -- */
#if defined cv_debug_
    cv_sptr i_debug_count;
#endif /* #if defined cv_debug_ */
};

void cv_object_load(void);

void cv_object_unload(void);

void cv_object_init(
    cv_object * p_this,
    char const * p_class,
    cv_uptr i_placement_len);

void cv_object_cleanup(
    cv_object * p_this);

void * cv_object_alloc(
    cv_object * p_this,
    cv_unique * r_unique);

void cv_object_free(
    cv_object * p_this,
    void * p_placement);

void cv_object_pick(
    cv_object * p_this,
    cv_unique * r_unique);

void cv_object_construct(
    cv_object * p_this,
    void * p_placement);

void cv_object_destruct(
    cv_object * p_this,
    void * p_placement);

#endif /* #ifndef cv_object_h_ */

/* end-of-file: cv_object.h */
