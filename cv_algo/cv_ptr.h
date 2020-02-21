/* See LICENSE for license details */

#ifndef cv_ptr_h_
#define cv_ptr_h_

typedef union cv_ptr cv_ptr;

union cv_ptr {
    void const * pc_void;
    void * p_void;
};

#define cv_ptr_initializer_(pc_void) { (pc_void) }

#endif /* #ifndef cv_ptr_h_ */

/* end-of-file: cv_ptr.h */
