/* See LICENSE for license details */

#ifndef cv_chunk_node_h_
#define cv_chunk_node_h_

/*
 *
 */

#include <cv_algo/cv_chunk_pred.h>
#include <cv_algo/cv_list_node.h>

/*
 *
 */

struct cv_chunk_node {
    cv_list_node o_node;
    unsigned char a_data[64u];
};

#define cv_chunk_node_initializer_ { cv_list_node_initializer_, {0} }

void cv_chunk_node_init(cv_chunk_node * p_this);
void cv_chunk_node_cleanup(cv_chunk_node * p_this);

#endif /* #ifndef cv_chunk_node_h_ */

/* end-of-file: cv_chunk_node.h */
