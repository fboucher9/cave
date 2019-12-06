/* See LICENSE for license details */

#ifndef cv_pool_h_
#define cv_pool_h_

/*
 *  Module: cv_pool.h
 *
 *  Description: Allocate objects of same size.  Each individual object is
 *  allocated from the main heap.  Free objects are kept in a list, to be
 *  reused at next allocation.  Synchronization must be handled by caller.
 *
 */

#include <cv_pool_pred.h>
#include <cv_pool_desc.h>
#include <cv_stack.h>

struct cv_pool {
    cv_pool_desc o_desc;
    /* -- */
    cv_stack o_free_list;
};

#define cv_pool_initializer_ \
{ cv_pool_desc_initializer_, cv_stack_initializer_ }

void cv_pool_init( cv_pool * p_this, cv_pool_desc const * p_desc);
void cv_pool_cleanup( cv_pool * p_this);
void * cv_pool_alloc( cv_pool * p_this);
void cv_pool_free( cv_pool * p_this, void * p_buffer);

#endif /* #ifndef cv_pool_h_ */

/* end-of-file: cv_pool.h */
