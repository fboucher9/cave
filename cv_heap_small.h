/* See LICENSE for license details */

#ifndef cv_heap_small_h_
#define cv_heap_small_h_

/*

Heap for allocations with small length, less than 4KB.

*/

#include <cv_heap_pred.h>
#include <cv_bool.h>
#include <cv_heap_pool.h>

#define cv_heap_small_max_len_ (4096)

#define cv_heap_small_align_ (16)

#define cv_heap_small_count_ (256)

typedef char cv_verify_heap_small_align [
    (cv_heap_small_align_ * cv_heap_small_count_) == cv_heap_small_max_len_
    ? 1 : -1 ];

struct cv_heap_small {
    cv_heap_pool a_pool[cv_heap_small_count_];
};

#define cv_heap_small_initializer_ { { cv_heap_pool_initializer_ } }

cv_bool cv_heap_small_init( cv_heap_small * p_this);

void cv_heap_small_cleanup( cv_heap_small * p_this);

cv_heap_node * cv_heap_small_lookup( cv_heap_small * p_this, long i_len);

cv_heap_node * cv_heap_small_alloc(
    cv_heap_primary * p_heap_primary,
    cv_heap_node_mgr * p_heap_node_mgr,
    long i_len);

void cv_heap_small_free( cv_heap_small * p_this, cv_heap_node * p_heap_node);

#endif /* #ifndef cv_heap_small_h_ */
