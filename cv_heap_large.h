/* See LICENSE for license details */

#ifndef cv_heap_large_h_
#define cv_heap_large_h_

#include <cv_heap_pred.h>
#include <cv_bool.h>

cv_bool cv_heap_large_load(void);
void cv_heap_large_unload(void);
cv_heap_node * cv_heap_large_alloc( long i_len);
void cv_heap_large_free( cv_heap_node * p_heap_node);

#endif /* #ifndef cv_heap_large_h_ */
