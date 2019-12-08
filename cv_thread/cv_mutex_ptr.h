/* See LICENSE for license details */

#ifndef cv_mutex_ptr_h_
#define cv_mutex_ptr_h_

/*

Module: cv_mutex_ptr.h

Description: Pointer to cv_mutex object.

*/

#include <cv_mutex_pred.h>

#include <cv_ptr.h>

union cv_mutex_ptr
{
    void const * pc_void;
    void * p_void;
    cv_mutex const * pc_mutex;
    cv_mutex * p_mutex;
};

#endif /* #ifndef cv_mutex_ptr_h_ */

/* end-of-file: cv_mutex_ptr.h */
