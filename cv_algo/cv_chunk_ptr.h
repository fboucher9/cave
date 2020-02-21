/* See LICENSE for license details */

#ifndef cv_chunk_ptr_h_
#define cv_chunk_ptr_h_

/*
 *
 */

#include <cv_algo/cv_chunk_pred.h>
#include <cv_algo/cv_list_pred.h>
#include <cv_algo/cv_list_ptr.h>

/*
 *
 */

union cv_chunk_ptr {
    void const * pc_void;
    void * p_void;
    cv_chunk_node const * pc_chunk;
    cv_chunk_node * p_chunk;
    cv_list_ptr o_list_ptr;
};

#endif /* #ifndef cv_chunk_ptr_h_ */

/* end-of-file: cv_chunk_ptr.h */
