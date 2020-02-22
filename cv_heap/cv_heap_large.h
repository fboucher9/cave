/* See LICENSE for license details */

#ifndef cv_heap_large_h_
#define cv_heap_large_h_

#include <cv_heap/cv_heap_pred.h>
#include <cv_thread/cv_mutex.h>
#include <cv_algo/cv_list_root.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

struct cv_heap_large {
    cv_mutex o_mutex;
    cv_list_root o_free_list;
};

cv_bool cv_heap_large_init( cv_heap_large * p_this);
void cv_heap_large_cleanup( cv_heap_large * p_this);
cv_heap_node * cv_heap_large_lookup( cv_heap_large * p_this, cv_uptr i_len);
cv_heap_node * cv_heap_large_alloc( cv_heap_secondary * p_heap_secondary,
    cv_uptr i_len);
void cv_heap_large_free( cv_heap_large * p_this, cv_heap_node * p_heap_node);

#endif /* #ifndef cv_heap_large_h_ */
