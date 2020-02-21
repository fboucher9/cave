/* See LICENSE for license details */

#ifndef cv_chunk_node_h_
#define cv_chunk_node_h_

/*
 *
 */

#include <cv_algo/cv_chunk_pred.h>
#include <cv_algo/cv_list_node.h>
#include <cv_misc/cv_types.h>

enum cv_chunk_node_consts {
    cv_chunk_data_len = 64
};

/*
 *
 */

struct cv_chunk_node {
    cv_list_node o_node;
    cv_uptr i_data_len;
    unsigned char a_data[cv_chunk_data_len];
};

void cv_chunk_node_init(cv_chunk_node * p_this);
void cv_chunk_node_cleanup(cv_chunk_node * p_this);
cv_bool cv_chunk_node_is_full(cv_chunk_node const * p_this);
cv_bool cv_chunk_node_write_char(cv_chunk_node * p_this,
    unsigned char i_value);

#endif /* #ifndef cv_chunk_node_h_ */

/* end-of-file: cv_chunk_node.h */
