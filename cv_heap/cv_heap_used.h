/* See LICENSE for license details */

#ifndef cv_heap_used_h_
#define cv_heap_used_h_

/*
 *  Module: cv_heap_used.h
 *
 *  Description: Cross reference to all used cv_heap_node structures.
 */

#include <cv_heap/cv_heap_pred.h>
#include <cv_mutex.h>
#include <cv_list_root.h>
#include <cv_bool.h>

/*
 *
 */

struct cv_heap_used {
    cv_mutex o_mutex;
    /* -- */
    cv_list_root o_used_list;
    /* -- */
    long i_count;
    long l_padding[1u];
};

#define cv_heap_used_initializer_ \
{ cv_mutex_initializer_, cv_list_root_initializer_, 0, {0} }

cv_bool cv_heap_used_init(
    cv_heap_used * p_this);

void cv_heap_used_cleanup(
    cv_heap_used * p_this);

void cv_heap_used_join(
    cv_heap_used * p_this,
    cv_heap_node * p_node);

cv_heap_node * cv_heap_used_lookup(
    cv_heap_used * p_this,
    void * p_buffer);

#endif /* #ifndef cv_heap_used_h_ */

/* end-of-file: cv_heap_used.h */
