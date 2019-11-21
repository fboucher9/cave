/* See LICENSE for license details */

#ifndef cv_mutex_mgr_h_
#define cv_mutex_mgr_h_

/*

*/

#include <cv_mutex_pred.h>

extern cv_mutex cv_heap_primary_mutex;

extern cv_mutex cv_heap_large_mutex;

cv_mutex * cv_mutex_mgr_acquire(void);

void cv_mutex_mgr_release(
    cv_mutex * p_this);

#endif /* #ifndef cv_mutex_mgr_h_ */

/* end-of-file: cv_mutex_mgr.h */
