/* See LICENSE for license details */

#ifndef cv_ptr_h_
#define cv_ptr_h_

#include <cv_null.h>

typedef union cv_ptr cv_ptr;

union cv_ptr
{
    void const * pc_void;
    void * p_void;
};

#define cv_ptr_null_ { cv_null_ }

#endif /* #ifndef cv_ptr_h_ */

/* end-of-file: cv_ptr.h */
