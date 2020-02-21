/* See LICENSE for license details */

#ifndef cv_chunk_it_h_
#define cv_chunk_it_h_

/*
 *  Module: cv_chunk_it.h
 *
 *  Description: Iterator for cv_chunk_node.
 */

#include <cv_algo/cv_chunk_pred.h>
#include <cv_algo/cv_chunk_ptr.h>
#include <cv_algo/cv_list_it.h>

/*
 *
 */

struct cv_chunk_it {
    cv_list_it o_list_it;
};

void cv_chunk_it_init(cv_chunk_it * p_this, cv_chunk_root const * p_root);
void cv_chunk_it_cleanup(cv_chunk_it * p_this);
cv_bool cv_chunk_it_next(cv_chunk_it * p_this, cv_chunk_ptr * r_ptr);

#endif /* #ifndef cv_chunk_it_h_ */

/* end-of-file: cv_chunk_it.h */
